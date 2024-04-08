#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
	unsigned long long chunks_sz;
	unsigned long long chunks_nb;
	unsigned long long alloc_delay;
	unsigned long long final_delay;
} alloc_conf_t;

static void set_default_conf(alloc_conf_t *conf)
{
	conf->chunks_sz = 0;
	conf->chunks_nb = 1;
	conf->alloc_delay = 0;
	conf->final_delay = 0;
}

static bool retrieve_conf(alloc_conf_t *conf)
{
	const char *schunks_sz = getenv("ALLOC_CHUNKS_SZ");
	const char *schunks_nb = getenv("ALLOC_CHUNKS_NB");
	const char *salloc_delay = getenv("ALLOC_DELAY");
	const char *sfinal_delay = getenv("ALLOC_FINAL_DELAY");

	set_default_conf(conf);
	if (!schunks_sz || strchr(schunks_sz, '-') || !(conf->chunks_sz = atoll(schunks_sz))) {
		fprintf(stderr, "ALLOC_CHUNKS_SZ must be set to a positive number.\n");
		return false;
	}
	if ((schunks_nb && strchr(schunks_nb, '-')) || (schunks_nb && !(conf->chunks_nb = atoll(schunks_nb)))) {
		fprintf(stderr, "ALLOC_CHUNKS_NB invalid. If set, must be a positive number.\n");
		return false;
	}
	if ((salloc_delay && strchr(salloc_delay, '-')) || (salloc_delay && !(conf->alloc_delay = atoll(salloc_delay)) && strcmp(salloc_delay, "0"))) {
		fprintf(stderr, "ALLOC_DELAY invalid. If set, must be a non-zero positive number.\n");
		return false;
	}
	if ((sfinal_delay && strchr(sfinal_delay, '-')) || (sfinal_delay && !(conf->final_delay = atoll(sfinal_delay)) && strcmp(sfinal_delay, "0"))) {
		fprintf(stderr, "ALLOC_FINAL_DELAY invalid. If set, must be a non-zero positive number.\n");
		return false;
	}
	return true;
}

volatile int main(int argc, char **argv)
{
	alloc_conf_t conf;
	char *buf;

	if (!retrieve_conf(&conf))
		return 1;
	printf("chunks_sz: %llu\nchunks_nb: %llu\nalloc_delay: %llu\nfinal_delay: %llu\n", conf.chunks_sz, conf.chunks_nb, conf.alloc_delay, conf.final_delay);
	for (unsigned long long i = 0; i < conf.chunks_nb; ++i) {
		printf("alloc %llu bytes (%llu / %llu)\n", conf.chunks_sz, i + 1, conf.chunks_nb);
		if (!(buf = malloc(conf.chunks_sz))) {
			perror("Fatal on malloc");
			return 1;
		}
		memset(buf, argc, conf.chunks_sz);
		usleep(conf.alloc_delay * 1000);
	}
	usleep(conf.final_delay * 1000);
	return 0;
}
