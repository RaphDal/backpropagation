
NAME		=		back

SRC_DIR		=		src
INC_DIR		=		include
BUILD_DIR	=		builds

SRC			:=		$(shell find $(SRC_DIR) -name '*.c' -type f)
INC			:=		$(shell find $(INC_DIR) -name '*.h' -type f)

OBJ			=		$(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

CFLAGS		=		-I $(INC_DIR) -g -I libraries/matrix
LDFLAGS		=		-L libraries/matrix -lmatrix -lm

all:	$(NAME)

$(NAME):	$(OBJ)
	$(MAKE) --no-print-directory -C libraries/matrix
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

$(BUILD_DIR)/%.o:	$(SRC_DIR)/%.c	$(INC)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(MAKE) --no-print-directory -C libraries/matrix clean
	$(RM) -r $(BUILD_DIR)
	$(RM) $(NAME)

re:	clean	all

.PHONY:	all	clean	re