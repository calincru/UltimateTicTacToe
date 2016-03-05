JC = javac
SRC_DIR = src
BUILD_DIR = bin
JCFLAGS = -sourcepath $(SRC_DIR) -d $(BUILD_DIR)
MAIN = $(SRC_DIR)/bot/BotStarter.java

JV = java
EXEC = bot.BotStarter
JVFLAGS = -cp $(BUILD_DIR)

build: $(BUILD_DIR)
	$(JC) $(JCFLAGS) $(MAIN)

$(BUILD_DIR):
	mkdir -p $@

run:
	$(JV) $(JVFLAGS) $(EXEC)

clean:
	rm -rf $(shell find $(SRC_DIR) -name "*.class") $(BUILD_DIR) &>/dev/null || true
