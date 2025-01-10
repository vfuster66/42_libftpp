NAME = libftpp.a

CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++11

SRCDIR = src
INCDIR = include
OBJDIR = obj
TESTDIR = tests

SRCS = $(wildcard $(SRCDIR)/**/*.cpp) $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

TEST_SRCS = $(wildcard $(TESTDIR)/*.cpp)
TEST_BINS = $(TEST_SRCS:$(TESTDIR)/%.cpp=%)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(TEST_BINS)

re: fclean all

test: all $(TEST_BINS)
	@for test in $(TEST_BINS); do \
		echo "Running $$test..."; \
		./$$test; \
	done

%: $(TESTDIR)/%.cpp $(NAME)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) $< -L. -lftpp -o $@

.PHONY: all clean fclean re test