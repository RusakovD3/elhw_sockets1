# Компилятор
CC = gcc

# Флаги компилятора
CFLAGS = -Wall

# Имена исполняемых файлов
INET_STREAM_SERVER_BIN = server_inet_stream
INET_STREAM_CLIENT_BIN = client_inet_stream
LOCAL_STREAM_SERVER_BIN = server_local_stream
LOCAL_STREAM_CLIENT_BIN = client_local_stream
INET_DGRAM_SERVER_BIN = server_inet_dgram
INET_DGRAM_CLIENT_BIN = client_inet_dgram
LOCAL_DGRAM_SERVER_BIN = server_local_dgram
LOCAL_DGRAM_CLIENT_BIN = client_local_dgram

# Псевдоцели
.PHONY: all clean inet_stream local_stream inet_dgram local_dgram

# Правило по умолчанию для сборки всех программ
all: inet_stream local_stream inet_dgram local_dgram

# Правила для индивидуальной сборки
inet_stream: $(INET_STREAM_SERVER_BIN) $(INET_STREAM_CLIENT_BIN)
local_stream: $(LOCAL_STREAM_SERVER_BIN) $(LOCAL_STREAM_CLIENT_BIN)
inet_dgram: $(INET_DGRAM_SERVER_BIN) $(INET_DGRAM_CLIENT_BIN)
local_dgram: $(LOCAL_DGRAM_SERVER_BIN) $(LOCAL_DGRAM_CLIENT_BIN)

# Сборка сервера и клиента для inet_stream
$(INET_STREAM_SERVER_BIN): server_inet_stream.c
	$(CC) $(CFLAGS) $^ -o $@

$(INET_STREAM_CLIENT_BIN): client_inet_stream.c
	$(CC) $(CFLAGS) $^ -o $@

# Сборка сервера и клиента для local_stream
$(LOCAL_STREAM_SERVER_BIN): server_local_stream.c
	$(CC) $(CFLAGS) $^ -o $@

$(LOCAL_STREAM_CLIENT_BIN): client_local_stream.c
	$(CC) $(CFLAGS) $^ -o $@

# Сборка сервера и клиента для inet_dgram
$(INET_DGRAM_SERVER_BIN): server_inet_dgram.c
	$(CC) $(CFLAGS) $^ -o $@

$(INET_DGRAM_CLIENT_BIN): client_inet_dgram.c
	$(CC) $(CFLAGS) $^ -o $@

# Сборка сервера и клиента для local_dgram
$(LOCAL_DGRAM_SERVER_BIN): server_local_dgram.c
	$(CC) $(CFLAGS) $^ -o $@

$(LOCAL_DGRAM_CLIENT_BIN): client_local_dgram.c
	$(CC) $(CFLAGS) $^ -o $@

# Очистка всех собранных файлов
clean:
	rm -f $(INET_STREAM_SERVER_BIN) $(INET_STREAM_CLIENT_BIN) \
	$(LOCAL_STREAM_SERVER_BIN) $(LOCAL_STREAM_CLIENT_BIN) \
	$(INET_DGRAM_SERVER_BIN) $(INET_DGRAM_CLIENT_BIN) \
	$(LOCAL_DGRAM_SERVER_BIN) $(LOCAL_DGRAM_CLIENT_BIN)
