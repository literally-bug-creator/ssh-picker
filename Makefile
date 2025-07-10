.PHONY: all debug release test benchmark format-check format static-analysis clean

BUILD_DIR = build
CXX = clang++
PROJECT_NAME = ssh-picker

all: release

debug:
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=$(CXX) ..
	@cd $(BUILD_DIR) && make -j$(shell nproc)

release:
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=$(CXX) ..
	@cd $(BUILD_DIR) && make -j$(shell nproc)

test:
	@cd $(BUILD_DIR) && ./tests/run_tests

format-check:
	@find . -name "*.cpp" -o -name "*.hpp" -o -name "*.h" -o -name "*.cc" | \
	grep -E "($(PROJECT_NAME))" | \
	grep -v "third-party" | \
	grep -v "build" | \
	xargs clang-format --dry-run --Werror --style=file:.clang-format

format:
	@find . -name "*.cpp" -o -name "*.hpp" -o -name "*.h" -o -name "*.cc" | \
	grep -E "($(PROJECT_NAME)|tests)" | \
	grep -v "third-party" | \
	grep -v "build" | \
	xargs clang-format -i --style=file:.clang-format

static-analysis: debug
	@find $(PROJECT_NAME) -name "*.cpp" -o -name "*.hpp" -o -name "*.h" | \
	xargs clang-tidy -p $(BUILD_DIR) --quiet --header-filter=".*"

clean:
	@rm -rf $(BUILD_DIR)
