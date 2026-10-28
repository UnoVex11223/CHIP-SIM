CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic

SRC = src
BUILD = build
OBJS = $(BUILD)/main.o $(BUILD)/pc.o $(BUILD)/ram8.o

$(BUILD)/chipsim: $(OBJS)
	@echo "Linking $@"
	@$(CC) $(CFLAGS) $^ -o $@

$(BUILD)/%.o: $(SRC)/%.c $(SRC)/*.h
	@mkdir -p $(BUILD)
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

run: $(BUILD)/chipsim
	@./$(BUILD)/chipsim

clean:
	@rm -rf $(BUILD)
	@echo "Clenaed"
