NAME = libftpp.a

CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++20

SRCDIR = src
INCDIR = include
OBJDIR = obj
TESTDIR = tests

SRCS = $(wildcard $(SRCDIR)/**/*.cpp) $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

HDRS = $(wildcard $(INCDIR)/**/*.hpp) $(wildcard $(INCDIR)/*.hpp)

TEST_SRCS = $(wildcard $(TESTDIR)/*.cpp)
TEST_BINS = $(TEST_SRCS:$(TESTDIR)/%.cpp=%)

# Couleurs
GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
BLUE = \033[0;34m
CYAN = \033[0;36m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HDRS)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(TEST_BINS)

re: fclean all

test: all $(TEST_BINS)
	@echo "$(CYAN)Starting tests...$(RESET)"
	@total_tests=0; passed_tests=0; failed_tests=0; \
	for test in $(TEST_BINS); do \
		total_tests=$$((total_tests + 1)); \
		echo "$(BLUE)Running $$test...$(RESET)"; \
		if ./$$test; then \
			echo "$(GREEN)$$test PASSED$(RESET)"; \
			passed_tests=$$((passed_tests + 1)); \
		else \
			echo "$(RED)$$test FAILED$(RESET)"; \
			failed_tests=$$((failed_tests + 1)); \
		fi; \
	done; \
	echo ""; \
	echo "$(CYAN)Tests Summary:$(RESET)"; \
	echo "$(YELLOW)Total tests:$$total_tests$(RESET)"; \
	echo "$(GREEN)Passed tests:$$passed_tests$(RESET)"; \
	echo "$(RED)Failed tests:$$failed_tests$(RESET)"; \
	if [ $$failed_tests -eq 0 ]; then \
		echo "$(GREEN)All tests PASSED! 🎉$(RESET)"; \
	else \
		echo "$(RED)Some tests FAILED. ❌$(RESET)"; \
		exit 1; \
	fi

%: $(TESTDIR)/%.cpp $(NAME) $(HDRS)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) $< -L. -lftpp -o $@

.PHONY: all clean fclean re test
