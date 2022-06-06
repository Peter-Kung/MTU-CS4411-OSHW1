#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <ctype.h>

#define max(x, y) ({ \
	typeof(x) _x = x; \
	typeof(y) _y = y; \
	(_x > _y)?_x:_y; \
		})

void *jobs(void *);

typedef struct tinfo {
	pthread_t tid;
	int *data;
	int *weight;
	int index1;
	int index2;
}T_INFO;

int main(int argc, char **argv)
{	
	int dataQuntity = atoi(argv[1]);
	int *data = (int *)malloc(sizeof(int) * dataQuntity);
	int *weight = (int *)malloc(sizeof(int) * dataQuntity);
	T_INFO *tinfo = NULL;
	pthread_attr_t attr;

	printf("Number of input values = %d\n", dataQuntity);
	printf("Input values         x = ");
	for (int i = 0;i < dataQuntity;i++) {
		data[i] = atoi(argv[i + 2]);
		weight[i] = 1;
		printf("%d ", data[i]);
	}
	puts("");
	printf("After initialization w = ");
	for (int i = 0;i < dataQuntity;i++) {
		printf("%d ", weight[i]);
	}
	puts("\n     ..........");
	
	
	pthread_attr_init(&attr);
	tinfo = (T_INFO *)malloc(sizeof(T_INFO) * dataQuntity * dataQuntity);
	for (int i = 0;i < dataQuntity;++i) {
		for (int j = i + 1;j < dataQuntity;++j) {
			int cur = i * dataQuntity + j;
			tinfo[cur].tid = cur;
			tinfo[cur].data = data;
			tinfo[cur].weight = weight;
			tinfo[cur].index1 = i;
			tinfo[cur].index2 = j;

			pthread_create(&tinfo[cur].tid,
					&attr,
					&jobs,
					&tinfo[cur]
					);
		}
	}

	pthread_attr_destroy(&attr);

	for (int i = 0;i < dataQuntity;++i)
		for (int j = i + 1;j < dataQuntity;j++) {
			int cur = i * dataQuntity + j;
			if (pthread_join(tinfo[cur].tid, NULL))
				perror("thread error");
		}

	int maxi, index;

	puts("     ..........");
	printf("After Step 2         w = ");
	for (int i = 0;i < dataQuntity;++i) {
		printf("%d ", weight[i]);
		if (weight[i]) {
			index = i;
			maxi = data[index];
		}
	}
	puts("");
	printf("Maximum                = %d\n", maxi);
	printf("Location               = %d\n", index);

	return 0;
}

void *jobs(void *argv)
{
	T_INFO *tinfo = (T_INFO *)argv;
	
	int index1 = tinfo->index1;
	int index2 = tinfo->index2;
	int *data = tinfo->data;
	int *weight = tinfo->weight;

	int index = (data[index1] > data[index2])?index2:index1;
	weight[index] = 0;
	printf("Thread T(%d,%d) compares x[%d] = %d and x[%d] = %d, and writes 0 into w[%d]\n",
			 index1, index2,
			 index1, data[index1],
			 index2, data[index2],
			 index);
}
