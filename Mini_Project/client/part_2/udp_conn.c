#include "miniproject.h"
#include "udp_conn.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#define IP_ADDRESS "192.168.0.1"
#define STRINGLENGTH 8
#define AVR_DOUBLE_CHAR_MAX_LENGTH 22

pthread_mutex_t udp_send_mutex;

struct udp_conn socket_conn;



char *double_to_char(double u_value,char u_arr[]){
//	#define STRINGLENGTH 8
	//char u_arr[STRINGLENGTH];
	sprintf(u_arr, "%f", u_value);


}

int udp_init(){
	pthread_mutex_init(&udp_send_mutex,NULL);
	return udp_init_client(&socket_conn,9999,IP_ADDRESS);
}

int send_start(){
	char msg[] = "START";
	pthread_mutex_lock(&udp_send_mutex);
	
	int ret = udp_send(&socket_conn,msg,strlen(msg)+1);
	pthread_mutex_unlock(&udp_send_mutex);
	return ret;
}

int send_get(){
	char msg[] = "GET";
	pthread_mutex_lock(&udp_send_mutex);
	int ret = udp_send(&socket_conn,msg,strlen(msg)+1);
	pthread_mutex_unlock(&udp_send_mutex);
	return ret;
}

int send_set(double u_value){
	//char u_arr[sizeof(u_value)];
	//memcpy(&u_arr, &u_value,sizeof(u_value));
	//char msg[] = "SET:";
	
	char number[AVR_DOUBLE_CHAR_MAX_LENGTH]; 
	double_to_char(u_value,number);

	char msg[AVR_DOUBLE_CHAR_MAX_LENGTH + 5];
	sprintf(msg,"%s","SET:\0");


	strcat(msg,number);




	int ret;
	pthread_mutex_lock(&udp_send_mutex);
	ret = udp_send(&socket_conn, msg, strlen(msg)+1);
	pthread_mutex_unlock(&udp_send_mutex);
	return ret;
	
}

int send_signal_ack(){
	char msg[] = "SIGNAL_ACK";
	pthread_mutex_lock(&udp_send_mutex);
	int ret = udp_send(&socket_conn,msg,strlen(msg)+1);
	pthread_mutex_unlock(&udp_send_mutex);
	return ret;
}

int send_stop(){
	char msg[] = "STOP";
	pthread_mutex_lock(&udp_send_mutex);
	int ret =  udp_send(&socket_conn,msg,5);
	pthread_mutex_unlock(&udp_send_mutex);
	return ret;
}




int receive_get(char buf[]){
	return udp_receive(&socket_conn,buf,256);
}
