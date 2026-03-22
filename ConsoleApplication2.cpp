// cs_chicken.c
// Written by <INSERT YOUR FULL NAME> <INSERT YOUR ZID> on <INSERT DATE>
//
// Description: <INSERT DESCRIPTION OF PROGRAM>

// Provided Libraries
#include <stdio.h>

// Add your own #include statements below this line

// Provided constants
#define COLS 10
#define ROWS 10
#define INVALID_ROW -1
#define INVALID_COL -1
#define INITIAL_POINTS 0
#define DEFAULT_POINT_TARGET 20

// Add your own #define constants below this line

// Provided Enums
// Enum for features on the game board
enum entity {
    EMPTY,
    COIN,
    TREE,
    ROAD,
    CAR_FACING_RIGHT,
    CAR_FACING_LEFT,
    HEADLIGHTS,
    KANGAROO,
    WOMBAT_TUNNEL,
    BABY_CHICKEN
};

// Add your own enums below this line

// Represents a tile on the board (you may edit this and add your own fields)
struct tile {
    enum entity entity;
};

// Add your own structs below this line

// Provided Function Prototypes
void print_welcome(void);
void initialise_board(struct tile board[ROWS][COLS]);
void print_board(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int curr_score,
    int target_score
);
void print_board_line(void);
void print_board_footer(int curr_score, int target_score);
void print_game_statistics(
    int turns_taken,
    int step_count,
    int coins,
    int score
);

// Additional Function Prototypes
void print_game_won(void);
void print_game_lost(void);

// Add your own function prototypes below this line
void setup_stage_1_1_print_banner(void);
void setup_stage_1_2_read_valid_start_position(int* player_row, int* player_col);
int setup_stage_1_3_process_basic_setup_commands(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    char command
);
int setup_stage_1_4_process_advanced_setup_commands(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int* target_score,
    char command
);
int setup_stage_2_4_process_target_score_command(
    int* target_score,
    char command
);
int gameplay_stage_2_4_handle_game_won(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int score,
    int target_score,
    int turns_taken,
    int step_count,
    int coins_collected
);
void gameplay_stage_2_1_start_gameplay_phase(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int score,
    int target_score
);

int gameplay_stage2_3_process_turn(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int* score,
    int* turns_taken,
    int* step_count,
    int* coins_collected,
    char command
);
int gameplay_stage_2_2_process_movement_validation(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    char command
);
int is_position_on_board(int row, int col);
int is_tile_occupied(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int row,
    int col
);
void place_basic_feature(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    enum entity feature
);
int can_build_road(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int row,
    int* deforesting
);
void build_road(struct tile board[ROWS][COLS], int row);
void place_car(
    struct tile board[ROWS][COLS],
    int row,
    int col,
    char direction
);

// Provided sample main() function (you will need to modify this)
int main(void) {
    print_welcome();

    struct tile board[ROWS][COLS];
    initialise_board(board);

    int player_row = INVALID_ROW;
    int player_col = INVALID_COL;
    int score = INITIAL_POINTS;
    int target_score = DEFAULT_POINT_TARGET;
    int turns_taken = 0;
    int step_count = 0;
    int coins_collected = 0;
    char command;

    setup_stage_1_1_print_banner();
    setup_stage_1_2_read_valid_start_position(&player_row, &player_col);


    print_board(
        board,
        player_row,
        player_col,
        score,
        target_score
    );

    printf("Enter setup commands:\n");
    while (scanf(" %c", &command) == 1 && command != 'e') {
        if (!setup_stage_1_3_process_basic_setup_commands(
            board, player_row, player_col, command
        )) {
            setup_stage_1_4_process_advanced_setup_commands(
                board, player_row, player_col, &target_score, command
            );
        }
    }

    if (!is_position_on_board(player_row, player_col)) {
        return 0;
    }

    gameplay_stage_2_1_start_gameplay_phase(
        board,
        player_row,
        player_col,
        score,
        target_score
    );

    while (scanf(" %c", &command) == 1) {
        int successful_move = 0;
        if (command == 'q') {
            printf("============= Quitting Game =============\n");
            return 0;
        }
        successful_move = gameplay_stage_2_2_process_movement_validation(
            board,
            &player_row,
            &player_col,
            command
        );


        if ((command == 'w' || command == 'a' || command == 's'
            || command == 'd' || command == 'R')
            && gameplay_stage_2_4_handle_game_won(
                board,
                player_row,
                player_col,
                score,
                target_score,
                turns_taken,
                step_count,
                coins_collected
            )) {
            return 0;
        }



        if (command == 'w' || command == 'a' || command == 's'
            || command == 'd' || command == 'R') {
            print_board(
                board,
                player_row,
                player_col,
                score,
                target_score
            );
        }
    }

    return 0;
}



int gameplay_stage2_3_process_turn(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int successful_move,
    int* score,
    int* turns_taken,
    int* step_count,
    int* coins_collected,
    char command
) {
    if (command == 'p') {
        print_game_statistics(
            *turns_taken,
            *step_count,
            *coins_collected,
            *score
        );
        return 0;
    }

    if (command == 'w' || command == 'a' || command == 's'
        || command == 'd' || command == 'R') {
        (*turns_taken)++;
    }
    if (command == 'w' || command == 'a' || command == 's'
        || command == 'd') {
        (*step_count)++;

        if (successful_move
            && is_position_on_board(player_row, player_col)
            && board[player_row][player_col].entity == COIN) {
            board[player_row][player_col].entity = EMPTY;
            *score += 5;
            (*coins_collected)++;
        }
    }

    return 0;

}

void setup_stage_1_1_print_banner(void) {
    printf("============== Setup Phase ==============\n")
}

// Add your function definitions below this line
void setup_stage_1_1_print_banner(void) {
    printf("============== Setup Phase ==============\n");
}

void setup_stage_1_2_read_valid_start_position(int* player_row,
    int* player_col) {
    while (!is_position_on_board(*player_row, *player_col)) {
        printf("Enter the starting position: ");
        if (scanf("%d %d", player_row, player_col) != 2) {
            return;
        }

        if (!is_position_on_board(*player_row, *player_col)) {
            printf("Penny the Chicken cannot start here!\n");
        }
    }
}

int setup_stage_1_3_process_basic_setup_commands(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    char command
) {
    if (command == 'c') {
        place_basic_feature(board, player_row, player_col, COIN);
        return 1;
    }
    else if (command == 't') {
        place_basic_feature(board, player_row, player_col, TREE);
        return 1;
    }

    return 0;
}

int setup_stage_1_4_process_advanced_setup_commands(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int* target_score,
    char command
) {
    int row;
    int col;
    int deforesting;
    char direction;

    if (command == 'r') {
        if (scanf("%d", &row) == 1) {
            if (row < 0 || row >= ROWS) {
                printf("Invalid location: position is not on map!\n");
            }
            else if (!can_build_road(
                board, player_row, player_col, row, &deforesting
            )) {
                printf("Invalid location: road cannot be built.\n");
            }
            else {
                if (deforesting) {
                    printf("Deforesting.\n");
                }
                build_road(board, row);
            }
        }
        return 1;
    }
    else if (command == 'v') {
        if (scanf("%d %d %c", &row, &col, &direction) == 3) {
            if (!is_position_on_board(row, col)) {
                printf("Invalid location: position is not on map!\n");
            }
            else if (board[row][col].entity != ROAD
                && board[row][col].entity != HEADLIGHTS) {
                printf("Invalid location: car must be on a road.\n");
            }
            else {
                place_car(board, row, col, direction);
            }
        }
        return 1;
    }
    else if (command == 'x') {
        setup_stage_2_4_process_target_score_command(
            target_score,
            command
        );

    }
    int setup_stage_2_4_process_target_score_command(
        int* target_score,
        char command
    ) {
        int points;

        if (command != 'x') {
            return 0;
        }

        if (scanf("%d", &points) == 1) {
            if (points < 1 || points > 99) {
                printf("Target must between 1 and 99 inclusive\n");
            }
            else {
                *target_score = points;
            }
        }

        return 1;
    }
    int gameplay_stage_2_4_handle_game_won(
        struct tile board[ROWS][COLS],
        int player_row,
        int player_col,
        int score,
        int target_score,
        int turns_taken,
        int step_count,
        int coins_collected
    ) {
        if (score < target_score) {
            return 0;
        }
        print_board(board, player_row, player_col, score, target_score);
        print_game_statistics(
            turns_taken,
            step_count,
            coins_collected,
            score
        );
        print_game_won();
        return 1;
    }
    void gameplay_stage_2_1_start_gameplay_phase(
        struct tile board[ROWS][COLS],
        int player_row,
        int player_col,
        int score,
        int target_score
    ) {
        static int gameplay_started = 0;

        if (!gameplay_started) {
            print_board(board, player_row, player_col, score, target_score);
            printf("============ Gameplay Phase =============\n");
            gameplay_started = 1;
        }
    }
    int gameplay_stage_2_2_process_movement_validation(
        struct tile board[ROWS][COLS],
        int* player_row,
        int* player_col,
        char command
    ) {
        int new_row = *player_row;
        int new_col = *player_col;

        if (command == 'w') {
            new_row--;
        }
        else if (command == 'a') {
            new_col--;
        }
        else if (command == 's') {
            new_row++;
        }
        else if (command == 'd') {
            new_col++;
        }
        else {
            return 0;
        }

        if (is_position_on_board(new_row, new_col)
            && board[new_row][new_col].entity != TREE) {
            *player_row = new_row;
            *player_col = new_col;
            return 1;
        }

        return 0;
    }

    int is_position_on_board(int row, int col) {
        return row >= 0 && row < ROWS && col >= 0 && col < COLS;
    }


    else if (command == 'v') {
        if (scanf("%d %d %c", &row, &col, &direction) == 3) {
            if (!is_position_on_board(row, col)) {
                printf("Invalid location: position is not on map!\n");
            }
            else if (board[row][col].entity != ROAD
                && board[row][col].entity != HEADLIGHTS) {
                printf("Invalid location: car must be on a road.\n");
            }
            else {
                place_car(board, row, col, direction);
            }
        }
        return 1;
    }
    else if (command == 'x') {
        if (scanf("%d", &row) == 1) {
            if (row < 1 || row > 99) {
                printf("Target must between 1 and 99 inclusive.\n");
            }
            else {
                *target_score = row;
            }
        }
        return 1;
    }
    return 0;
}

void gameplay_stage_2_1_start_gameplay_phase(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int score,
    int target_score
) {
    print_board(board, player_row, player_col, score, target_score);
    printf("============ Gameplay Phase =============\n");
}

int is_position_on_board(int row, int col) {
    return row >= 0 && row < ROWS && col >= 0 && col < COLS;
}

int is_tile_occupied(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int row,
    int col
) {
    return (row == player_row && col == player_col)
        || board[row][col].entity != EMPTY;
}

void place_basic_feature(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    enum entity feature
) {
    int row;
    int col;

    if (scanf("%d %d", &row, &col) == 2) {
        if (!is_position_on_board(row, col)) {
            printf("Invalid location: position is not on map!\n");
        }
        else if (is_tile_occupied(board, player_row, player_col, row, col)) {
            printf("Invalid location: tile is occupied!\n");
        }
        else {
            board[row][col].entity = feature;
        }
    }
}

int can_build_road(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int row,
    int* deforesting
) {
    int col;

    *deforesting = 0;
    for (col = 0; col < COLS; col++) {
        if (row == player_row && col == player_col) {
            return 0;
        }
        if (board[row][col].entity == COIN
            || board[row][col].entity == CAR_FACING_RIGHT
            || board[row][col].entity == CAR_FACING_LEFT
            || board[row][col].entity == HEADLIGHTS) {
            return 0;
        }
        if (board[row][col].entity == TREE) {
            *deforesting = 1;
        }
    }

    return 1;
}

void build_road(struct tile board[ROWS][COLS], int row) {
    for (int col = 0; col < COLS; col++) {
        board[row][col].entity = ROAD;
    }
}

void place_car(
    struct tile board[ROWS][COLS],
    int row,
    int col,
    char direction
) {
    if (direction == 'r') {
        board[row][col].entity = CAR_FACING_RIGHT;
        if (col + 1 < COLS && board[row][col + 1].entity == ROAD) {
            board[row][col + 1].entity = HEADLIGHTS;
        }
    }
    else if (direction == 'l') {
        board[row][col].entity = CAR_FACING_LEFT;
        if (col - 1 >= 0 && board[row][col - 1].entity == ROAD) {
            board[row][col - 1].entity = HEADLIGHTS;
        }
    }
}


// =============================================================================
// Provided Helper Functions
// =============================================================================

// Prints the game's welcome banner
void print_welcome(void) {
    printf(
        "_________________________________________   \n"
        "   \\\\                               \\\\  \n"
        "   (o>   !!    Welcome to    !!     (o>     \n"
        "\\\\_//)         CS CHICKEN        \\\\_//) \n"
        " \\_/_)                            \\_/_)   \n"
        "  _|_                              _|_      \n"
        "_________________________________________   \n\n"
    );
}

// Given a 2D board array, initialises all tile entities to EMPTY.
void initialise_board(struct tile board[ROWS][COLS]) {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            board[row][col].entity = EMPTY;
        }
    }
}

// Prints the game board, showing the player's position, current score and 
// target score
void print_board(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int curr_score,
    int target_score
) {
    print_board_line();
    printf("|          C S   C H I C K E N          |\n");
    print_board_line();

    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            printf("|");
            if (row == player_row && col == player_col) {
                printf("^_^");
            }
            else if (board[row][col].entity == EMPTY) {
                printf("   ");
            }
            else if (board[row][col].entity == COIN) {
                printf(" c ");
            }
            else if (board[row][col].entity == TREE) {
                printf(" T ");
            }
            else if (board[row][col].entity == ROAD) {
                printf("___");
            }
            else if (board[row][col].entity == CAR_FACING_RIGHT) {
                printf("[_0");
            }
            else if (board[row][col].entity == CAR_FACING_LEFT) {
                printf("0_]");
            }
            else if (board[row][col].entity == HEADLIGHTS) {
                printf("###");
            }
            else {
                printf("   ");
            }
        }
        printf("|\n");
        print_board_line();
    }

    print_board_footer(curr_score, target_score);
    printf("\n");
}

// Helper function to print statistics. 
// Use in Stage 2.3.
void print_game_statistics(
    int turns_taken,
    int step_count,
    int coins,
    int score
) {
    printf(
        "============ Game Statistics ============\n"
        "          Turns taken: %d\n"
        "           Step count: %d\n"
        "      Coins Collected: %d\n"
        "                Score: %d\n",
        turns_taken, step_count, coins, score
    );
}

// Helper function to print the banner for when the game is won. 
// Use in Stage 2.4
void print_game_won(void) {
    printf(
        "_________________________________________   \n"
        "       Penny the Chicken is happy!          \n"
        "   \\\\                               \\\\  \n"
        "   (o>   !!    Thank  you    !!     (o>     \n"
        "\\\\_//)        for playing!       \\\\_//) \n"
        " \\_/_)                            \\_/_)   \n"
        "  _|_                              _|_      \n"
        "_________________________________________   \n\n"
    );
}

// Helper function to print the banner for when the game is won. 
// Use in Stage 3.1
void print_game_lost(void) {
    printf(
        "_________________________________________   \n"
        "   \\\\                               \\\\  \n"
        "   (x>    !!      Game      !!      (x>     \n"
        "\\\\_//)             Over          \\\\_//) \n"
        " \\_/_)                            \\_/_)   \n"
        "  _|_                              _|_      \n"
        "_________________________________________   \n\n"
    );
}

///////////////////////////////////////////////////////////////////////////////
// Additional Provided Functions
///////////////////////////////////////////////////////////////////////////////

// You don't need to use any of these, or understand how they work!
// We use them to implement some of the provided helper functions.

// Helper function for print_board(). 
void print_board_footer(int curr_score, int target_score) {
    printf("Score: %-3d                     ", curr_score);
    printf("Target: %-2d", target_score);
}

// Helper function for print_board(). 
void print_board_line(void) {
    printf("+");
    for (int col = 0; col < COLS; col++) {
        printf("---+");
    }
    printf("\n");
}






