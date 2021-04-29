#include <zephyr.h>

#include <stdio.h>
#include <string.h>

#include <net/http_parser.h>

#include <logging/log.h>
LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

static const char get[] = 
"GET /hello/mysuperconformistefriend/jetaimepas/23/aul/eZ/qs23 HTTP/1.1\r\n"\
"Host: 192.168.10.233:8080\r\n"\
"User-Agent: curl/7.74.0\r\n"\
"Accept: */*\r\n\r\n";

static const char post[] = 
"POST /urls HTTP/1.1\r\n"\
"Content-Type: application/json\r\n"\
"User-Agent: PostmanRuntime/7.28.0\r\n"\
"Accept: */*\r\n"\
"Postman-Token: 5c3edb00-8fe6-4065-9aa0-0071a8bf9bdd\r\n"\
"Host: 192.168.10.233:8080\r\n"\
"Accept-Encoding: gzip, deflate, br\r\n"\
"Connection: keep-alive\r\n"\
"Content-Length: 65\r\n"\
"\r\n"
"{\r\n"\
"    \"content\": 23,\r\n"\
"    \"hello\": \"hzef\",\r\n"\
"    \"temp\": 23.24\r\n"\
"}\r\n";

int on_url(struct http_parser * parser, const char *at, size_t length)
{
    LOG_HEXDUMP_DBG(at, length, "on_url");

    return 0;
}

int on_status(struct http_parser * parser, const char *at, size_t length)
{
    LOG_HEXDUMP_DBG(at, length, "on_status");

    return 0;
}

int on_header_field(struct http_parser * parser, const char *at, size_t length)
{
    LOG_HEXDUMP_DBG(at, length, "on_header_field");

    return 0;
}

int on_header_value(struct http_parser * parser, const char *at, size_t length)
{
    LOG_HEXDUMP_DBG(at, length, "on_header_value");

    return 0;
}

int on_body(struct http_parser * parser, const char *at, size_t length)
{
    LOG_HEXDUMP_DBG(at, length, "on_body");

    return 0;
}

int on_message_complete(struct http_parser * parser)
{
    LOG_DBG("on_message_complete - parser state : %d", parser->state);

    return 0;
}

const struct http_parser_settings settings = {
    .on_url = on_url,
    .on_status = on_status,
    .on_header_field = on_header_field,
    .on_header_value = on_header_value,
    .on_body = on_body,
    .on_message_complete = on_message_complete,
};

void parse(const char * buffer)
{
    struct http_parser parser;
    
    http_parser_init(&parser, HTTP_REQUEST);

    size_t ret;

    LOG_DBG("parsing request of size %u", strlen(buffer));

    ret = http_parser_execute(&parser, &settings, buffer, 50);

    LOG_DBG("http_parser_execute %d/%d", ret, 50);

    ret = http_parser_execute(&parser, &settings, &buffer[50], strlen(&buffer[50]));

    LOG_DBG("http_parser_execute %d/%d", ret, strlen(&buffer[50]));
}

void main(void)
{
    parse(get);
    
    LOG_DBG("====================");

    parse(post);
}
