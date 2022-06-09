#ifdef RL_LIBCURL

extern int curl_global_init_once(long flags);
extern int curl_https_get(const char *url, int timeout, int retry, uint8_t **data, size_t *data_alloc);
extern size_t curl_http_get_buf(const char *url, int timeout, int retry, buffer_t *buf);

enum { NO_RETRY, ONE_RETRY, INF_RETRY };

#endif
