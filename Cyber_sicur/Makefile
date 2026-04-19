NAME_SPIDER := spider
NAME_SCORPION := scorpion

CXX := c++
CXXFLAGS := -Wall -Wextra -Werror -std=c++17
CURL_CFLAGS := $(shell pkg-config --cflags libcurl 2>/dev/null)
CURL_LIBS := $(shell pkg-config --libs libcurl 2>/dev/null)
INCLUDES := -Iinclude -Iinclude/common -Iinclude/spider -Iinclude/scorpion $(CURL_CFLAGS)

COMMON_SRCS := \
	src/common/PathUtils.cpp

SPIDER_SRCS := \
	src/spider/main.cpp \
	src/spider/SpiderController.cpp \
	src/spider/HttpClient.cpp \
	src/spider/HtmlParser.cpp \
	src/spider/UrlUtils.cpp \
	src/spider/FileManager.cpp

SCORPION_SRCS := \
	src/scorpion/main.cpp \
	src/scorpion/MetadataReader.cpp \
	src/scorpion/MetadataPrinter.cpp \
	src/scorpion/FileValidator.cpp

SPIDER_OBJS := $(SPIDER_SRCS:.cpp=.o)
SCORPION_OBJS := $(SCORPION_SRCS:.cpp=.o)
COMMON_OBJS := $(COMMON_SRCS:.cpp=.o)

all: $(NAME_SPIDER) $(NAME_SCORPION)

$(NAME_SPIDER): $(SPIDER_OBJS) $(COMMON_OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@ $(CURL_LIBS)

$(NAME_SCORPION): $(SCORPION_OBJS) $(COMMON_OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(SPIDER_OBJS) $(SCORPION_OBJS) $(COMMON_OBJS)

fclean: clean
	rm -f $(NAME_SPIDER) $(NAME_SCORPION)

re: fclean all

.PHONY: all clean fclean re
