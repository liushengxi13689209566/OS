/*************************************************************************
	> File Name: combine.c
	> Author: Liu Shengxi 
	> Mail: 13689209566@163.com
	> Created Time: 2018年06月20日 星期三 20时10分27秒
 ************************************************************************/

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#define IDENT 1
#define OP  *
typedef long data_t ;
typedef struct {
	long len ;
	data_t *data ;
}vec_rec,*vec_ptr ;
vec_ptr new_vec(long len){
	vec_ptr  result = (vec_ptr)malloc(sizeof(vec_ptr));
	data_t *data = NULL ;
	if( !result ){
		return NULL ;
	}
	result->len = len ;
	if( len > 0 ){
		data =(data_t *)calloc(len,sizeof(data_t));
		if( !data  ){
			free((void *)result);
			return NULL ;
		}
	}
	result->data = data ;
	for (int i = 0; i < len ; ++i)
	{
		result->data[i] = i + 1 ;
	}
	return result ;
}
int get_vec_element(vec_ptr v,long index ,data_t *dest){
	if(index < 0 | index >= v->len ){
		return 0;
	}
	*dest = v->data[index];
	return 1;
}
long vec_length(vec_ptr  v){
	return v->len ;
}
data_t* get_vec_start(vec_ptr  v){
	return v->data ;
}
void combine1(const vec_ptr v, data_t *dest){
	long i ;
	*dest = IDENT ;
	for ( i = 0; i < vec_length(v) ; ++i)
	{
		data_t val ;
		get_vec_element(v,i,&val);
		*dest = *dest OP val ;
	}
}
/* 2. 消除循环的低效率*/
void combine2(const vec_ptr v, data_t *dest){  //代码移动，识别要进行多次，但是计算结果不会改变的计算
	long i ;
	*dest = IDENT ;
	long length = vec_length(v) ;
	for ( i = 0; i < length ; ++i)
	{
		data_t val ;
		get_vec_element(v,i,&val);
		*dest = *dest OP val ;
	}
}
/* 3. 减少过程调用 */
void combine3(const vec_ptr v, data_t *dest){  
	long i ;
	*dest = IDENT ;
	long length = vec_length(v) ;
	data_t *data = get_vec_start(v);
	for ( i = 0; i < length ; ++i)
	{
		*dest = *dest OP data[i] ;
	}
}
/* 4.消除不必要的内存引用  */
void combine4(const vec_ptr v, data_t *dest){  
	long i ;
	long length = vec_length(v) ;
	data_t *data = get_vec_start(v);
	data_t acc = IDENT ;
	for ( i = 0; i < length ; ++i)
	{
		acc = acc OP data[i] ;
	}
	*dest = acc ;
}
/* 4b. 执行边界检查  */
void combine4b(const vec_ptr v, data_t *dest){  
	long i ;
	long length = vec_length(v) ;
	data_t acc = IDENT ;
	for ( i = 0; i < length ; ++i)
	{
		if(i >= 0 && i < v->len )
			acc = acc OP v->data[i] ;
	}
	*dest = acc ;
}
/*5.循环展开，通过增加每次迭代计算的数量，减少循环次数*/
void combine5(const vec_ptr v, data_t *dest){  
	long i ;
	long length = vec_length(v) ;
	long limit = length - 1;
	data_t *data = get_vec_start(v);
	data_t acc = IDENT ;
	for ( i = 0; i < limit ; i+=2 )//2x1 循环展开
	{
		acc = (acc OP data[i]) OP data[i+1] ;
	}
	for(; i< length ;i++ ){
		acc =  acc OP data[i];
	}
	*dest = acc ;
}
/*6.多个累计变量 */
void combine6(const vec_ptr v, data_t *dest){  
	long i ;
	long length = vec_length(v) ;
	long limit = length - 1;
	data_t *data = get_vec_start(v);
	data_t acc0 = IDENT ;
	data_t acc1 = IDENT ;
	for ( i = 0; i < limit ; i+=2 ) // 2x1 循环展开
	{
		acc0 = acc0  OP data[i] ;
		acc1 = acc1  OP data[i+1];
	}
	for(; i< length ;i++ ){
		acc0 =  acc0 OP data[i];
	}
	*dest = acc0 OP acc1  ;
}

/*7. 重新结合变换 */
void combine7(const vec_ptr v, data_t *dest){  
	long i ;
	long length = vec_length(v) ;
	long limit = length - 1;
	data_t *data = get_vec_start(v);
	data_t acc = IDENT ;
	for ( i = 0; i < limit ; i+=2 )//2x1 循环展开
	{
		acc = acc OP (data[i] OP data[i+1]) ;
	}
	for(; i< length ;i++ ){
		acc =  acc OP data[i];
	}
	*dest = acc ;
}

void print_vec(const vec_ptr v ){
	for (int i = 0; i < v->len; ++i)
	{
		printf("%ld   ", v->data[i]);
	}
	printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n" );
}
int main(int argc, char const *argv[])
{
	clock_t start,end ;
	double dt = 0 ; 
	vec_ptr tmp_ptr  = new_vec(99999999);
	data_t  tmp_data ;

	start =  clock() ;
	tmp_data = 0 ;
	combine1(tmp_ptr,&tmp_data);
	end = clock();
	dt =(double)(end - start ) ;
	printf("OP  result ===  %ld\n", tmp_data );
	printf("combine1  == %lf\n", dt/ CLOCK_TAI );
	printf("\n");





	start =  clock() ;
	tmp_data = 0 ;
	combine2(tmp_ptr,&tmp_data);
	end = clock();
	dt =(double)(end - start ) ;
	printf("OP  result ===  %ld\n", tmp_data );
	printf("combine2  == %lf\n", dt/ CLOCK_TAI );
	printf("\n");




	start =  clock() ;
	tmp_data = 0 ;
	combine3(tmp_ptr,&tmp_data);
	end = clock();
	dt =(double)(end - start ) ;
	printf("OP  result ===  %ld\n", tmp_data );
	printf("combine3  == %lf\n", dt/ CLOCK_TAI );
	printf("\n");
	
	



	start =  clock() ;
	tmp_data = 0 ;
	combine4(tmp_ptr,&tmp_data);
	end = clock();
	dt =(double)(end - start ) ;
	printf("OP  result ===  %ld\n", tmp_data );
	printf("combine4  == %lf\n", dt/ CLOCK_TAI );
	printf("\n");




	start =  clock() ;
	tmp_data = 0 ;
	combine4b(tmp_ptr,&tmp_data);
	end = clock();
	dt =(double)(end - start ) ;
	printf("OP  result ===  %ld\n", tmp_data );
	printf("combine4b  == %lf\n", dt/ CLOCK_TAI );
	printf("\n");



	start =  clock() ;
	tmp_data = 0 ;
	combine5(tmp_ptr,&tmp_data);
	end = clock();
	dt =(double)(end - start ) ;
	printf("OP  result ===  %ld\n", tmp_data );
	printf("combine5  == %lf\n", dt/ CLOCK_TAI );
	printf("\n");







	start =  clock() ;
	tmp_data = 0 ;
	combine6(tmp_ptr,&tmp_data);
	end = clock();
	dt =(double)(end - start ) ;
	printf("OP  result ===  %ld\n", tmp_data );
	printf("combine6  == %lf\n", dt/ CLOCK_TAI );
	printf("\n");





	start =  clock() ;
	tmp_data = 0 ;
	combine7(tmp_ptr,&tmp_data);
	end = clock();
	dt =(double)(end - start ) ;
	printf("OP  result ===  %ld\n", tmp_data );
	printf("combine7  == %lf\n", dt/ CLOCK_TAI );
	printf("\n");
	return 0;
}

