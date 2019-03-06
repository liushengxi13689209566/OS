static __poll_t ep_send_events_proc(struct eventpoll *ep, struct list_head *head,
                                    void *priv)
{
    struct ep_send_events_data *esed = priv;
    __poll_t revents;
    struct epitem *epi;
    struct epoll_event __user *uevent;
    struct wakeup_source *ws;
    poll_table pt;

    init_poll_funcptr(&pt, NULL);

    /*
	 * We can loop without lock because we are passed a task private list.
	 * Items cannot vanish during the loop because ep_scan_ready_list() is
	 * holding "mtx" during this call.
	 */
    for (esed->res = 0, uevent = esed->events;
         !list_empty(head) && esed->res < esed->maxevents;)
    {
        epi = list_first_entry(head, struct epitem, rdllink);

        /*
		 * Activate ep->ws before deactivating epi->ws to prevent
		 * triggering auto-suspend here (in case we reactive epi->ws
		 * below).
		 *
		 * This could be rearranged to delay the deactivation of epi->ws
		 * instead, but then epi->ws would temporarily be out of sync
		 * with ep_is_linked().
		 */
        ws = ep_wakeup_source(epi);
        if (ws)
        {
            if (ws->active)
                __pm_stay_awake(ep->ws);
            __pm_relax(ws);
        }

        list_del_init(&epi->rdllink);

        revents = ep_item_poll(epi, &pt, 1);

        /*
		 * If the event mask intersect the caller-requested one,
		 * deliver the event to userspace. Again, ep_scan_ready_list()
		 * is holding "mtx", so no operations coming from userspace
		 * can change the item.
		 */
        if (revents)
        {
            if (__put_user(revents, &uevent->events) ||
                __put_user(epi->event.data, &uevent->data))
            {
                list_add(&epi->rdllink, head);
                ep_pm_stay_awake(epi);
                if (!esed->res)
                    esed->res = -EFAULT;
                return 0;
            }
            esed->res++;
            uevent++;
            if (epi->event.events & EPOLLONESHOT)
                epi->event.events &= EP_PRIVATE_BITS;
            else if (!(epi->event.events & EPOLLET))
            {
                /*
				 * If this file has been added with Level
				 * Trigger mode, we need to insert back inside
				 * the ready list, so that the next call to
				 * epoll_wait() will check again the events
				 * availability. At this point, no one can insert
				 * into ep->rdllist besides us. The epoll_ctl()
				 * callers are locked out by
				 * ep_scan_ready_list() holding "mtx" and the
				 * poll callback will queue them in ep->ovflist.
				 */
                list_add_tail(&epi->rdllink, &ep->rdllist);
                ep_pm_stay_awake(epi);
            }
        }
    }

    return 0;
}