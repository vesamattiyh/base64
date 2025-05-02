all:
	gcc -Wall -g -o b64 main.c base64.c tests/test_base64.c