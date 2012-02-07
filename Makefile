CC		=	mpicc
RM		=	rm -vf

MASTER_DIR	=	COMP428-A1-Parallel-Spawn
SLAVE_DIR	=	COMP428-A1-Parallel-Spawn
SHARED_DIR	=	COMP428-A1-Shared
PROD_DIR	=	DerivedData/COMP428-A1/Build/Products
INTER_DIR	=	DerivedData/COMP428-A1/Build/Intermediates/COMP428-A1.build

MASTER_NAME	=	COMP428-A1-Parallel-Spawn-Master
SLAVE_NAME	=	COMP428-A1-Parallel-Spawn-Slave

MASTER_SRC	=	$(MASTER_DIR)/master.c
MASTER_OBJ	=	$(MASTER_SRC:.c=.o)

SLAVE_SRC	=	$(SLAVE_DIR)/slave.c
SLAVE_OBJ	=	$(SLAVE_SRC:.c=.o)

SHARED_SRC	=	$(SHARED_DIR)/dboard.c
SHARED_OBJ	=	$(SHARED_SRC:.c=.o)

INCLUDE		=	-I./$(SHARED_DIR)
CFLAGS		=	-W -Wall $(INCLUDE)

debug: CFLAGS += -g
debug: BUILD_DIR = $(PROD_DIR)/Debug
debug: all

release: BUILD_DIR = $(PROD_DIR)/Release
release: all

create_directories:
	@mkdir -p $(INTER_DIR)/$(MASTER_DIR)
	@mkdir -p $(INTER_DIR)/$(SLAVE_DIR)
	@mkdir -p $(INTER_DIR)/$(SHARED_DIR)
	@mkdir -p $(BUILD_DIR)

all: create_directories $(MASTER_NAME) $(SLAVE_NAME)

$(MASTER_NAME): $(MASTER_OBJ) $(SHARED_OBJ)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$(MASTER_NAME) $(INTER_DIR)/$(MASTER_OBJ) $(INTER_DIR)/$(SHARED_OBJ)

$(SLAVE_NAME): $(SLAVE_OBJ) $(SHARED_OBJ)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$(SLAVE_NAME) $(INTER_DIR)/$(SLAVE_OBJ) $(INTER_DIR)/$(SHARED_OBJ)


.c.o:
	$(CC) $(CFLAGS) -c $< -o $(INTER_DIR)/$@

clean:
	$(RM) $(INTER_DIR)$(MASTER_OBJ) $(INTER_DIR)$(SLAVE_OBJ) $(INTER_DIR)$(SHARED_OBJ)

fclean: clean
	$(RM) -r $(PROD_DIR)

.PHONY: $(MASTER_NAME) $(SLAVE_NAME) release debug all clean fclean
