#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "curl/curl.h"
#include <stdbool.h>
#include <regex.h>

typedef struct
{
	char* header;
	char* link;
	char* audio_name;
	int resolution;


} m3u8;


m3u8 * parse_m3u8_file()
{
	m3u8 * m3u8_array;
	m3u8_array = malloc (100 * sizeof(m3u8));
	FILE *fp;

	regex_t regex;
	int reti;
	char * line = NULL;
	char* str_line;
	char* sub_line;

	size_t len = 0;
	ssize_t read;

	int i = 0;
	char sharp = '#';
	char two_dot = ':';
	char comma = ',';
	char equal = '=';

	reti = regcomp(&regex, "\\b(\\w*EXT-X-STREAM-INF\\w*)\\b", 0); // \b(\w*EXT-X-STREAM-INF\w*)\b


	printf("read output.m3u8");
	fp = fopen("output.m3u8","r");

    while ((read = getline(&line, &len, fp)) != -1) {
    	int resolution = 0;
    	char* link = NULL;
    	char* audio_name = NULL;
    	bool is_point = false;

    	char * my_line = line;

    	// example lines
		// #EXT-X-STREAM-INF:AVERAGE-BANDWIDTH=4775338,BANDWIDTH=5054232,CODECS="avc1.64002a,mp4a.40.2",RESOLUTION=1920x1080,FRAME-RATE=60.000,CLOSED-CAPTIONS="cc1",AUDIO="aud1",SUBTITLES="sub1"
		// v7/prog_index.m3u8

    	if(read > 1)
    	{

    		//TODO Parse line for each parameter
    		// first , with ':'
    		// and with ',',
    		// and with '='
    		reti = regexec(&regex, line, 0, NULL, 0);
    		if (reti) {
    		    for (char c = *my_line; c; c=*++my_line) {
					if (':' == c) {

					}
				}
    		    // get audio name , resolution and link and inset to m3u8 struct
    		    is_point = true;
    		}
    		else if(is_point)
    		{
    			// get audio link
    			m3u8_array--;
    			m3u8_array->link = line;
    			m3u8_array++;
    			is_point = false;
    		}
    	}
	}
    regfree(&regex);
    fclose(fp);

    return m3u8_array;
}

void get_high_resolution_version_and_concatenate(){
	//TODO
	// parameter : m3u8_array
	// find high resolution varinat and download for each AUDIO
	// get variants witl libcrul
	//finally concatenate them
}

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}

int main(int argc, char *argv[]) {
	CURLcode res = curl_global_init(CURL_GLOBAL_ALL);
	CURL *curl;
	FILE *fp,*fp_ts;
	m3u8 * m3u8_struct;


	for (int i = 0; i < argc; ++i) {
			printf("%d \n",argc);
			printf("argv[ %d ] = %s\n", i, argv[i]);
		}
	if (argc < 3) {
			printf("Missing arguments download link and output file ... \n");
			printf("Program is closing...");
			exit(-1);
		}

	curl = curl_easy_init();
	if (curl)
	{
		fp = fopen("output.m3u8","wb");
		curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
		curl_easy_setopt (curl, CURLOPT_VERBOSE, 1L);
		res = curl_easy_perform(curl);
		fclose(fp);

		m3u8_struct = parse_m3u8_file();
		get_high_resolution_version_and_concatenate();

		curl_easy_cleanup(curl);
		printf("curl_easy_cleanup(curl)\n");

	}


	printf("Program is closing...");
	return 0;
}
