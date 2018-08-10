#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

class PageReplacement {
private:
    vector<int> page;
    int page_num;  //物理内存块数
public:
    PageReplacement() : page_num(0) {}
    void create();
    void print();
    void physical_block_print( const vector<int>& );
    bool isfind( const vector<int>&, int );  //查找是否已在内存物理块中
    void FIFO();  //FIFO页面置换算法
    void LRU();  //LRU页面置换算法
    void OPT(); //OPT页面置换算法
};

void PageReplacement::create() {
    cout << "请输入页面个数: ";
    int n, t;
    cin >> n;

    cout << "请输入页面串：\n";
    while( n-- ) {
        cin >> t;
        page.push_back( t );
    }

    cout << "请输入内存物理块数: ";
    cin >> page_num;
}

void PageReplacement::print() {
    int n = page.size();
    cout << "页面串:\n";
    for( int i = 0; i < n; i++ ) {
        cout << page[i] << ' ';
    }
    cout << endl;
}

void PageReplacement::physical_block_print( const vector<int>& t ) {
    int n = t.size();
    for( int i = 0; i < n; i++ ) {
        cout << t[i] << ' ';
    }
    cout << endl;
}

bool PageReplacement::isfind( const vector<int> & block, int t ) {
    if ( find( block.begin(), block.end(), t ) != block.end() ) {
        return true;
    }
    return false;
}

/* FIFO页面置换算法 */
void PageReplacement::FIFO() {
    vector<int> physical_block( page_num, -1 );

    int n = page.size(), cur = 0;
    int not_found = 0;
    cout << "FIFO页面置换情况:\n";
    for( int i = 0; i < n; i++ ) {
        if( !isfind( physical_block, page[i] ) ) {
            physical_block[cur] = page[i];  //页面置换
            cur = (cur+1)%page_num;
            not_found++;
        }
        physical_block_print( physical_block );  //输出每个物理块信息
    }

    cout << "缺页次数："<< not_found << endl;
}

/* LRU页面置换算法 */
void PageReplacement::LRU() {
    vector<int> physical_block( page_num, -1 );
    map<int, int> page_time;
    int n = page.size();
    int not_found = 0;

    for( int i = 0; i < n; i++ ) {
        if ( !isfind( physical_block, page[i] ) ) {  //当前页不在为物理块中
            if ( page_time.size() < page_num ) { //物理块未放满
                physical_block[i] = page[i];
                page_time[page[i]] = i;
            } else {  //物理块放满，进行页面置换
                map<int, int>::iterator it = page_time.begin(), t = it;
                for( it++; it != page_time.end(); it++ ) {
                    if ( t->second > it->second ) {
                        t = it;
                    }
                }
                int index;
                for( index = 0; index < page_num && physical_block[index]!=t->first; index++ )
                    ;
                physical_block[index] = page[i];
                page_time.erase( t );
                page_time[page[i]] = i;
            }
            not_found++;
        } else {  //在物理块中，更新页面最后使用时间
            page_time[page[i]] = i;
        }
        physical_block_print( physical_block );
    }

    cout << "缺页次数："<< not_found << endl;
}

/* OPT页面置换算法 */
void PageReplacement::OPT() {
    vector<int> physical_block( page_num, -1 );
    int n = page.size();
    int not_found = 0;

    for( int i = 0; i < n; i++ ) {
        if( !isfind( physical_block, page[i] ) ) {  //当前页不在物理块中
            if( i < page_num ) {  //物理块未放满
                physical_block[i] = page[i];
            } else {  //物理块放满,进行页面置换
                map<int, int> page_time;
                int k, j;

                /* 获取物理块中页面此后的最先使用时间 */
                for( j = 0; j < page_num; j++ ) { //遍历physical_block
                    for( k = i+1; k < n; k++ ) {  //遍历page
                        if( physical_block[j] == page[k] ) {
                            page_time[page[k]] = k;
                            break;
                        }
                    }
                    if( k == n ) {
                        page_time[physical_block[j]] = k;
                    }
                }

                /* 寻找可以置换的页面 */
                map<int, int>::iterator it = page_time.begin(), t = it;
                for( ; it != page_time.end(); it++ ) {
                    if ( t->second < it->second ) {
                        t = it;
                    }
                }

                /* 获取被置换页面在物理块的下标 */
                int index = 0;
                for( ; index < page_num && physical_block[index] != t->first; index++ )
                    ;
                physical_block[index] = page[i];
            }
            not_found++;
        }
        physical_block_print( physical_block );
    }

    cout << "缺页次数："<< not_found << endl;
}

int main() {
    PageReplacement t;
    t.create();
    // t.FIFO();
    t.LRU();
    // t.OPT();

    return 0;
}