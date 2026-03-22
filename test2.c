// test2.c
// Extracted Stage 2.2 and Stage 2.3 logic

// Provided Libraries
#include <stdio.h>

// Add your own #include statements below this line


// Provided constants
#define COLS 10
#define ROWS 10

// Add your own #define constants below this line
#define MAX_TUNNELS 10
#define INVALID_ROW -1
#define INVALID_COL -1
#define INVALID_TUNNEL_ID -1
#define INITIAL_POINTS 0
#define DEFAULT_POINT_TARGET 20


// Provided Enums
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


// Represents a tile on the board
struct tile {
    enum entity entity;
    int tunnel_id;
};

// Add your own structs below this line
enum game_mode {
    STATIC_MODE,
    DRIVING_MODE,
    SCROLLING_MODE
};


// Provided Function Prototypes
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
void print_game_won(void);
void print_game_lost(void);

// Add your own function prototypes below this line
void print_welcome(void);
void initialise_board(struct tile board[ROWS][COLS]);
int main(void);
int is_position_on_board(int row, int col);
int is_tile_occupied(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int row,
    int col
);
void setup_stage_1_1_print_setup_banner(void);
void setup_stage_1_2_read_valid_start_position(int *player_row, int *player_col);
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
    int *target_score,
    enum game_mode *mode,
    char command
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
    int *deforesting
);
void build_road(struct tile board[ROWS][COLS], int row);
void place_car(
    struct tile board[ROWS][COLS],
    int row,
    int col,
    char direction
);
int setup_stage_3_4_process_wombat_tunnel_command(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col
);
int gameplay_stage_3_4_find_tunnel_exit(
    struct tile board[ROWS][COLS],
    int entry_row,
    int entry_col,
    int *exit_row,
    int *exit_col
);
int gameplay_stage_3_4_attempt_tunnel_move(
    struct tile board[ROWS][COLS],
    int original_row,
    int original_col,
    int *player_row,
    int *player_col,
    char command,
    int *successful_move
);
void gameplay_stage_3_4_start_static_mode(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int score,
    int target_score
);
int gameplay_stage_3_4_process_static_turn(
    struct tile board[ROWS][COLS],
    int *player_row,
    int *player_col,
    int *score,
    int target_score,
    int *turns_taken,
    int *step_count,
    int *coins_collected,
    char command
);
int gameplay_stage_2_2_process_movement_validation(
    struct tile board[ROWS][COLS],
    int *player_row,
    int *player_col,
    char command,
    int *successful_move
);
int gameplay_stage_2_3_process_coin_collection_and_stats(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    char command,
    int successful_move,
    int *score,
    int target_score,
    int *turns_taken,
    int *step_count,
    int *coins_collected
);
int setup_stage_2_4_process_target_score_command(
    int *target_score,
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
void gameplay_stage_3_1_print_board_with_shocked_chicken(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int curr_score,
    int target_score
);
int gameplay_stage_3_1_player_is_shocked(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col
);
int gameplay_stage_3_1_handle_collision(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int score,
    int target_score,
    int turns_taken,
    int step_count,
    int coins_collected
);
int setup_stage_3_2_is_driving_mode_command(char command);
int gameplay_stage_3_2_is_turn_command(char command);
int gameplay_stage_3_2_is_movement_command(char command);
int gameplay_stage_3_2_is_car(enum entity entity);
int gameplay_stage_3_2_is_valid_car_destination(
    struct tile board[ROWS][COLS],
    int row,
    int col
);
void gameplay_stage_3_2_clear_headlights(struct tile board[ROWS][COLS]);
void gameplay_stage_3_2_refresh_headlights(struct tile board[ROWS][COLS]);
void gameplay_stage_3_2_process_left_facing_cars(
    struct tile board[ROWS][COLS],
    int moved[ROWS][COLS]
);
void gameplay_stage_3_2_process_right_facing_cars(
    struct tile board[ROWS][COLS],
    int moved[ROWS][COLS]
);
void gameplay_stage_3_2_run_car_turn(struct tile board[ROWS][COLS]);
int gameplay_stage_3_2_process_turn(
    struct tile board[ROWS][COLS],
    int *player_row,
    int *player_col,
    int *score,
    int target_score,
    int *turns_taken,
    int *step_count,
    int *coins_collected,
    char command
);
void gameplay_stage_3_2_start_driving_mode(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int score,
    int target_score
);
int setup_stage_3_3_is_scrolling_mode_command(char command);
void gameplay_stage_3_3_initialise_coin_map(
    struct tile board[ROWS][COLS],
    int coin_map[ROWS][COLS]
);
void gameplay_stage_3_3_rotate_board_rows(
    struct tile board[ROWS][COLS],
    int row_ids[ROWS]
);
void gameplay_stage_3_3_restore_top_row_coins(
    struct tile board[ROWS][COLS],
    int coin_map[ROWS][COLS],
    int row_ids[ROWS]
);
int gameplay_stage_3_3_collect_coin(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int *score,
    int *coins_collected
);
int gameplay_stage_3_3_attempt_scroll(
    struct tile board[ROWS][COLS],
    int *player_row,
    int player_col,
    int *score,
    int target_score,
    int *turns_taken,
    int *step_count,
    int *coins_collected,
    int coin_map[ROWS][COLS],
    int row_ids[ROWS],
    int started_on_top_row,
    int moved_up
);
int gameplay_stage_3_3_process_turn(
    struct tile board[ROWS][COLS],
    int *player_row,
    int *player_col,
    int *score,
    int target_score,
    int *turns_taken,
    int *step_count,
    int *coins_collected,
    int coin_map[ROWS][COLS],
    int row_ids[ROWS],
    char command
);
void gameplay_stage_3_3_start_scrolling_mode(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int score,
    int target_score
);

static int g_next_tunnel_id = 0;
static int g_last_move_used_tunnel = 0;

// Add your function definitions below this line
int gameplay_stage_2_2_process_movement_validation(
    struct tile board[ROWS][COLS],
    int *player_row,
    int *player_col,
    char command,
    int *successful_move
) {
    int original_row = *player_row;
    int original_col = *player_col;
    int new_row = *player_row;
    int new_col = *player_col;

    g_last_move_used_tunnel = 0;

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

    if (is_position_on_board(new_row, new_col)
        && board[new_row][new_col].entity != TREE) {
        *player_row = new_row;
        *player_col = new_col;
        if (board[new_row][new_col].entity == WOMBAT_TUNNEL) {
            return gameplay_stage_3_4_attempt_tunnel_move(
                board,
                original_row,
                original_col,
                player_row,
                player_col,
                command,
                successful_move
            );
        }

        *successful_move = 1;
        return 1;
    }

    return 0;
}

int gameplay_stage_2_3_process_coin_collection_and_stats(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    char command,
    int successful_move,
    int *score,
    int target_score,
    int *turns_taken,
    int *step_count,
    int *coins_collected
) {
    if (command == 'p') {
        print_game_statistics(
            *turns_taken,
            *step_count,
            *coins_collected,
            *score
        );
    }

    if (command == 'w' || command == 'a' || command == 's'
        || command == 'd' || command == 'R') {
        (*turns_taken)++;
    }

    if ((command == 'w' || command == 'a' || command == 's'
            || command == 'd')
        && board[player_row][player_col].entity == COIN) {
        board[player_row][player_col].entity = EMPTY;
        *score += 5;
        (*coins_collected)++;
    }

    if ((command == 'w' || command == 'a' || command == 's'
            || command == 'd' || command == 'R')
        && *score >= target_score) {
        print_board(board, player_row, player_col, *score, target_score);
        print_game_statistics(
            *turns_taken,
            *step_count + successful_move,
            *coins_collected,
            *score
        );
        print_game_won();
        return 1;
    }

    return 0;
}

int setup_stage_2_4_process_target_score_command(
    int *target_score,
    char command
) {
    int points;

    if (command != 'x') {
        return 0;
    }

    if (scanf("%d", &points) == 1) {
        if (points < 1 || points > 99) {
            printf("Target must be between 1 and 99 inclusive.\n");
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

void gameplay_stage_3_1_print_board_with_shocked_chicken(
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
                if (gameplay_stage_3_1_player_is_shocked(
                        board, player_row, player_col
                    )) {
                    printf("0_0");
                }
                else {
                    printf("^_^");
                }
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
            else if (board[row][col].entity == WOMBAT_TUNNEL) {
                printf("(%d)", board[row][col].tunnel_id);
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

int gameplay_stage_3_1_player_is_shocked(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col
) {
    return board[player_row][player_col].entity == HEADLIGHTS;
}

int gameplay_stage_3_1_handle_collision(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int score,
    int target_score,
    int turns_taken,
    int step_count,
    int coins_collected
) {
    if (board[player_row][player_col].entity != CAR_FACING_LEFT
        && board[player_row][player_col].entity != CAR_FACING_RIGHT) {
        return 0;
    }

    gameplay_stage_3_1_print_board_with_shocked_chicken(
        board,
        player_row,
        player_col,
        score,
        target_score
    );
    print_game_statistics(
        turns_taken,
        step_count,
        coins_collected,
        score
    );
    print_game_lost();
    return 1;
}

int setup_stage_3_2_is_driving_mode_command(char command) {
    return command == 'd';
}

int setup_stage_3_3_is_scrolling_mode_command(char command) {
    return command == 's';
}

int gameplay_stage_3_2_is_turn_command(char command) {
    return command == 'w' || command == 'a' || command == 's'
        || command == 'd' || command == 'R';
}

int gameplay_stage_3_2_is_movement_command(char command) {
    return command == 'w' || command == 'a' || command == 's'
        || command == 'd';
}

int gameplay_stage_3_2_is_car(enum entity entity) {
    return entity == CAR_FACING_LEFT || entity == CAR_FACING_RIGHT;
}

int gameplay_stage_3_2_is_valid_car_destination(
    struct tile board[ROWS][COLS],
    int row,
    int col
) {
    if (!is_position_on_board(row, col)) {
        return 0;
    }

    return board[row][col].entity == ROAD
        || board[row][col].entity == HEADLIGHTS;
}

void gameplay_stage_3_2_clear_headlights(struct tile board[ROWS][COLS]) {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            if (board[row][col].entity == HEADLIGHTS) {
                board[row][col].entity = ROAD;
            }
        }
    }
}

void gameplay_stage_3_2_refresh_headlights(struct tile board[ROWS][COLS]) {
    gameplay_stage_3_2_clear_headlights(board);

    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            if (board[row][col].entity == CAR_FACING_RIGHT
                && is_position_on_board(row, col + 1)
                && board[row][col + 1].entity == ROAD) {
                board[row][col + 1].entity = HEADLIGHTS;
            }
            else if (board[row][col].entity == CAR_FACING_LEFT
                && is_position_on_board(row, col - 1)
                && board[row][col - 1].entity == ROAD) {
                board[row][col - 1].entity = HEADLIGHTS;
            }
        }
    }
}

void gameplay_stage_3_2_process_left_facing_cars(
    struct tile board[ROWS][COLS],
    int moved[ROWS][COLS]
) {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            if (moved[row][col]
                || board[row][col].entity != CAR_FACING_LEFT) {
                continue;
            }

            if (gameplay_stage_3_2_is_valid_car_destination(
                    board, row, col - 1
                )) {
                board[row][col].entity = ROAD;
                board[row][col - 1].entity = CAR_FACING_LEFT;
                moved[row][col - 1] = 1;
            }
            else {
                board[row][col].entity = CAR_FACING_RIGHT;
                moved[row][col] = 1;
            }
        }
    }
}

void gameplay_stage_3_2_process_right_facing_cars(
    struct tile board[ROWS][COLS],
    int moved[ROWS][COLS]
) {
    for (int row = 0; row < ROWS; row++) {
        for (int col = COLS - 1; col >= 0; col--) {
            if (moved[row][col]
                || board[row][col].entity != CAR_FACING_RIGHT) {
                continue;
            }

            if (gameplay_stage_3_2_is_valid_car_destination(
                    board, row, col + 1
                )) {
                board[row][col].entity = ROAD;
                board[row][col + 1].entity = CAR_FACING_RIGHT;
                moved[row][col + 1] = 1;
            }
            else {
                board[row][col].entity = CAR_FACING_LEFT;
                moved[row][col] = 1;
            }
        }
    }
}

void gameplay_stage_3_2_run_car_turn(struct tile board[ROWS][COLS]) {
    int moved[ROWS][COLS] = {{0}};

    gameplay_stage_3_2_process_left_facing_cars(board, moved);
    gameplay_stage_3_2_process_right_facing_cars(board, moved);
    gameplay_stage_3_2_refresh_headlights(board);
}

void gameplay_stage_3_3_initialise_coin_map(
    struct tile board[ROWS][COLS],
    int coin_map[ROWS][COLS]
) {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            coin_map[row][col] = board[row][col].entity == COIN;
        }
    }
}

void gameplay_stage_3_3_rotate_board_rows(
    struct tile board[ROWS][COLS],
    int row_ids[ROWS]
) {
    struct tile bottom_row[COLS];
    int bottom_row_id = row_ids[ROWS - 1];

    for (int col = 0; col < COLS; col++) {
        bottom_row[col] = board[ROWS - 1][col];
    }

    for (int row = ROWS - 1; row > 0; row--) {
        for (int col = 0; col < COLS; col++) {
            board[row][col] = board[row - 1][col];
        }
        row_ids[row] = row_ids[row - 1];
    }

    for (int col = 0; col < COLS; col++) {
        board[0][col] = bottom_row[col];
    }
    row_ids[0] = bottom_row_id;
}

void gameplay_stage_3_3_restore_top_row_coins(
    struct tile board[ROWS][COLS],
    int coin_map[ROWS][COLS],
    int row_ids[ROWS]
) {
    int source_row = row_ids[0];

    for (int col = 0; col < COLS; col++) {
        if (coin_map[source_row][col] && board[0][col].entity == EMPTY) {
            board[0][col].entity = COIN;
        }
    }
}

int gameplay_stage_3_3_collect_coin(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int *score,
    int *coins_collected
) {
    if (board[player_row][player_col].entity != COIN) {
        return 0;
    }

    board[player_row][player_col].entity = EMPTY;
    *score += 5;
    (*coins_collected)++;
    return 1;
}

int gameplay_stage_3_3_attempt_scroll(
    struct tile board[ROWS][COLS],
    int *player_row,
    int player_col,
    int *score,
    int target_score,
    int *turns_taken,
    int *step_count,
    int *coins_collected,
    int coin_map[ROWS][COLS],
    int row_ids[ROWS],
    int started_on_top_row,
    int moved_up
) {
    if (!started_on_top_row && !moved_up) {
        return 0;
    }

    if (started_on_top_row && board[ROWS - 1][player_col].entity == TREE) {
        return 0;
    }

    gameplay_stage_3_3_rotate_board_rows(board, row_ids);
    gameplay_stage_3_3_restore_top_row_coins(board, coin_map, row_ids);

    if (started_on_top_row) {
        (*step_count)++;
        gameplay_stage_3_3_collect_coin(
            board,
            *player_row,
            player_col,
            score,
            coins_collected
        );

        if (gameplay_stage_3_1_handle_collision(
                board,
                *player_row,
                player_col,
                *score,
                target_score,
                *turns_taken,
                *step_count,
                *coins_collected
            )) {
            return 1;
        }

        if (gameplay_stage_2_4_handle_game_won(
                board,
                *player_row,
                player_col,
                *score,
                target_score,
                *turns_taken,
                *step_count,
                *coins_collected
            )) {
            return 1;
        }

        return 0;
    }

    (*player_row)++;
    return 0;
}

int gameplay_stage_3_2_process_turn(
    struct tile board[ROWS][COLS],
    int *player_row,
    int *player_col,
    int *score,
    int target_score,
    int *turns_taken,
    int *step_count,
    int *coins_collected,
    char command
) {
    int successful_move = 0;

    if (command == 'q') {
        printf("============= Quitting Game =============\n");
        return 1;
    }

    if (command == 'p') {
        print_game_statistics(
            *turns_taken,
            *step_count,
            *coins_collected,
            *score
        );
        return 0;
    }

    if (!gameplay_stage_3_2_is_turn_command(command)) {
        return 0;
    }

    (*turns_taken)++;

    if (gameplay_stage_3_2_is_movement_command(command)) {
        g_last_move_used_tunnel = 0;
        gameplay_stage_2_2_process_movement_validation(
            board,
            player_row,
            player_col,
            command,
            &successful_move
        );
        *step_count += successful_move;

        if (successful_move
            && board[*player_row][*player_col].entity == COIN) {
            board[*player_row][*player_col].entity = EMPTY;
            *score += 5;
            (*coins_collected)++;
        }

        if (gameplay_stage_3_1_handle_collision(
                board,
                *player_row,
                *player_col,
                *score,
                target_score,
                *turns_taken,
                *step_count,
                *coins_collected
            )) {
            return 1;
        }
    }

    if (gameplay_stage_2_4_handle_game_won(
            board,
            *player_row,
            *player_col,
            *score,
            target_score,
            *turns_taken,
            *step_count,
            *coins_collected
        )) {
        return 1;
    }

    gameplay_stage_3_2_run_car_turn(board);

    if (gameplay_stage_3_1_handle_collision(
            board,
            *player_row,
            *player_col,
            *score,
            target_score,
            *turns_taken,
            *step_count,
            *coins_collected
        )) {
        return 1;
    }

    print_board(
        board,
        *player_row,
        *player_col,
        *score,
        target_score
    );
    return 0;
}

void gameplay_stage_3_2_start_driving_mode(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int score,
    int target_score
) {
    int turns_taken = 0;
    int step_count = 0;
    int coins_collected = 0;
    char command;

    print_board(board, player_row, player_col, score, target_score);
    printf("============ Gameplay Phase =============\n");

    while (scanf(" %c", &command) == 1) {
        if (gameplay_stage_3_2_process_turn(
                board,
                &player_row,
                &player_col,
                &score,
                target_score,
                &turns_taken,
                &step_count,
                &coins_collected,
                command
            )) {
            return;
        }
    }
}

int main(void) {
    struct tile board[ROWS][COLS];
    int player_row = INVALID_ROW;
    int player_col = INVALID_COL;
    int score = INITIAL_POINTS;
    int target_score = DEFAULT_POINT_TARGET;
    enum game_mode mode = STATIC_MODE;
    char command;

    print_welcome();
    initialise_board(board);

    setup_stage_1_1_print_setup_banner();
    setup_stage_1_2_read_valid_start_position(&player_row, &player_col);
    print_board(board, player_row, player_col, score, target_score);

    printf("Enter setup commands:\n");
    while (scanf(" %c", &command) == 1 && command != 'e') {
        if (!setup_stage_1_3_process_basic_setup_commands(
                board, player_row, player_col, command
            )) {
            setup_stage_1_4_process_advanced_setup_commands(
                board,
                player_row,
                player_col,
                &target_score,
                &mode,
                command
            );
        }
    }

    if (mode == DRIVING_MODE) {
        gameplay_stage_3_2_start_driving_mode(
            board,
            player_row,
            player_col,
            score,
            target_score
        );
    }
    else if (mode == SCROLLING_MODE) {
        gameplay_stage_3_3_start_scrolling_mode(
            board,
            player_row,
            player_col,
            score,
            target_score
        );
    }
    else {
        gameplay_stage_3_4_start_static_mode(
            board,
            player_row,
            player_col,
            score,
            target_score
        );
    }

    return 0;
}

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

void initialise_board(struct tile board[ROWS][COLS]) {
    g_next_tunnel_id = 0;
    g_last_move_used_tunnel = 0;

    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            board[row][col].entity = EMPTY;
            board[row][col].tunnel_id = INVALID_TUNNEL_ID;
        }
    }
}

void setup_stage_1_1_print_setup_banner(void) {
    printf("============== Setup Phase ==============\n");
}

void setup_stage_1_2_read_valid_start_position(int *player_row, int *player_col) {
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
    if (command == 't') {
        place_basic_feature(board, player_row, player_col, TREE);
        return 1;
    }

    return 0;
}

void place_basic_feature(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    enum entity feature
) {
    int row;
    int col;

    if (scanf("%d %d", &row, &col) != 2) {
        return;
    }

    if (!is_position_on_board(row, col)) {
        printf("Invalid location: position is not on map!\n");
    }
    else if (is_tile_occupied(board, player_row, player_col, row, col)) {
        printf("Invalid location: tile is occupied!\n");
    }
    else {
        board[row][col].entity = feature;
        board[row][col].tunnel_id = INVALID_TUNNEL_ID;
    }
}

int can_build_road(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int row,
    int *deforesting
) {
    *deforesting = 0;

    for (int col = 0; col < COLS; col++) {
        if (row == player_row && col == player_col) {
            return 0;
        }
        if (board[row][col].entity == COIN
            || board[row][col].entity == CAR_FACING_RIGHT
            || board[row][col].entity == CAR_FACING_LEFT
            || board[row][col].entity == HEADLIGHTS
            || board[row][col].entity == WOMBAT_TUNNEL) {
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
        board[row][col].tunnel_id = INVALID_TUNNEL_ID;
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
        board[row][col].tunnel_id = INVALID_TUNNEL_ID;
        if (col + 1 < COLS && board[row][col + 1].entity == ROAD) {
            board[row][col + 1].entity = HEADLIGHTS;
            board[row][col + 1].tunnel_id = INVALID_TUNNEL_ID;
        }
    }
    else if (direction == 'l') {
        board[row][col].entity = CAR_FACING_LEFT;
        board[row][col].tunnel_id = INVALID_TUNNEL_ID;
        if (col - 1 >= 0 && board[row][col - 1].entity == ROAD) {
            board[row][col - 1].entity = HEADLIGHTS;
            board[row][col - 1].tunnel_id = INVALID_TUNNEL_ID;
        }
    }
}

int setup_stage_1_4_process_advanced_setup_commands(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int *target_score,
    enum game_mode *mode,
    char command
) {
    int row;
    int col;
    int deforesting;
    char direction;
    char subcommand;

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
    if (command == 'v') {
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
    if (command == 'x') {
        return setup_stage_2_4_process_target_score_command(target_score, command);
    }
    if (command == 'd') {
        *mode = DRIVING_MODE;
        return 1;
    }
    if (command == 's') {
        *mode = SCROLLING_MODE;
        return 1;
    }
    if (command == 'w') {
        if (scanf(" %c", &subcommand) == 1 && subcommand == 't') {
            return setup_stage_3_4_process_wombat_tunnel_command(
                board,
                player_row,
                player_col
            );
        }
    }

    return 0;
}

int setup_stage_3_4_process_wombat_tunnel_command(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col
) {
    int row_1;
    int col_1;
    int row_2;
    int col_2;

    if (scanf("%d %d %d %d", &row_1, &col_1, &row_2, &col_2) != 4) {
        return 1;
    }

    if (g_next_tunnel_id >= MAX_TUNNELS) {
        printf("Invalid feature: too many tunnels!\n");
        return 1;
    }

    if (!is_position_on_board(row_1, col_1)
        || !is_position_on_board(row_2, col_2)
        || is_tile_occupied(board, player_row, player_col, row_1, col_1)
        || is_tile_occupied(board, player_row, player_col, row_2, col_2)) {
        printf("Invalid location: wombat couldn't dig a tunnel here!\n");
        return 1;
    }

    board[row_1][col_1].entity = WOMBAT_TUNNEL;
    board[row_1][col_1].tunnel_id = g_next_tunnel_id;
    board[row_2][col_2].entity = WOMBAT_TUNNEL;
    board[row_2][col_2].tunnel_id = g_next_tunnel_id;
    g_next_tunnel_id++;
    return 1;
}

int gameplay_stage_3_4_find_tunnel_exit(
    struct tile board[ROWS][COLS],
    int entry_row,
    int entry_col,
    int *exit_row,
    int *exit_col
) {
    int tunnel_id = board[entry_row][entry_col].tunnel_id;

    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            if ((row != entry_row || col != entry_col)
                && board[row][col].entity == WOMBAT_TUNNEL
                && board[row][col].tunnel_id == tunnel_id) {
                *exit_row = row;
                *exit_col = col;
                return 1;
            }
        }
    }

    return 0;
}

int gameplay_stage_3_4_attempt_tunnel_move(
    struct tile board[ROWS][COLS],
    int original_row,
    int original_col,
    int *player_row,
    int *player_col,
    char command,
    int *successful_move
) {
    int exit_row;
    int exit_col;
    int row_delta = 0;
    int col_delta = 0;
    int destination_row;
    int destination_col;

    if (!gameplay_stage_3_4_find_tunnel_exit(
            board, *player_row, *player_col, &exit_row, &exit_col
        )) {
        *player_row = original_row;
        *player_col = original_col;
        return 0;
    }

    if (command == 'w') {
        row_delta = -1;
    }
    else if (command == 'a') {
        col_delta = -1;
    }
    else if (command == 's') {
        row_delta = 1;
    }
    else if (command == 'd') {
        col_delta = 1;
    }

    destination_row = exit_row + row_delta;
    destination_col = exit_col + col_delta;
    if (!is_position_on_board(destination_row, destination_col)
        || board[destination_row][destination_col].entity == TREE) {
        *player_row = original_row;
        *player_col = original_col;
        *successful_move = 0;
        return 0;
    }

    *player_row = destination_row;
    *player_col = destination_col;
    *successful_move = 1;
    g_last_move_used_tunnel = 1;
    return 1;
}

int gameplay_stage_3_4_process_static_turn(
    struct tile board[ROWS][COLS],
    int *player_row,
    int *player_col,
    int *score,
    int target_score,
    int *turns_taken,
    int *step_count,
    int *coins_collected,
    char command
) {
    int successful_move = 0;

    if (command == 'q') {
        printf("============= Quitting Game =============\n");
        return 1;
    }

    if (command == 'p') {
        print_game_statistics(
            *turns_taken,
            *step_count,
            *coins_collected,
            *score
        );
        return 0;
    }

    if (command != 'w' && command != 'a' && command != 's' && command != 'd') {
        return 0;
    }

    (*turns_taken)++;
    gameplay_stage_2_2_process_movement_validation(
        board,
        player_row,
        player_col,
        command,
        &successful_move
    );
    *step_count += successful_move;

    if (successful_move && board[*player_row][*player_col].entity == COIN) {
        board[*player_row][*player_col].entity = EMPTY;
        board[*player_row][*player_col].tunnel_id = INVALID_TUNNEL_ID;
        *score += 5;
        (*coins_collected)++;
    }

    if (gameplay_stage_2_4_handle_game_won(
            board,
            *player_row,
            *player_col,
            *score,
            target_score,
            *turns_taken,
            *step_count,
            *coins_collected
        )) {
        return 1;
    }

    print_board(board, *player_row, *player_col, *score, target_score);
    return 0;
}

void gameplay_stage_3_4_start_static_mode(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int score,
    int target_score
) {
    int turns_taken = 0;
    int step_count = 0;
    int coins_collected = 0;
    char command;

    print_board(board, player_row, player_col, score, target_score);
    printf("============ Gameplay Phase =============\n");
    while (scanf(" %c", &command) == 1) {
        if (gameplay_stage_3_4_process_static_turn(
                board,
                &player_row,
                &player_col,
                &score,
                target_score,
                &turns_taken,
                &step_count,
                &coins_collected,
                command
            )) {
            return;
        }
    }
}

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
            else if (board[row][col].entity == WOMBAT_TUNNEL) {
                printf("(%d)", board[row][col].tunnel_id);
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

void print_board_footer(int curr_score, int target_score) {
    printf("Score: %-3d                     ", curr_score);
    printf("Target: %-2d", target_score);
}

void print_board_line(void) {
    printf("+");
    for (int col = 0; col < COLS; col++) {
        printf("---+");
    }
    printf("\n");
}

int gameplay_stage_3_3_process_turn(
    struct tile board[ROWS][COLS],
    int *player_row,
    int *player_col,
    int *score,
    int target_score,
    int *turns_taken,
    int *step_count,
    int *coins_collected,
    int coin_map[ROWS][COLS],
    int row_ids[ROWS],
    char command
) {
    int successful_move = 0;
    int original_row = *player_row;

    if (command == 'q') {
        printf("============= Quitting Game =============\n");
        return 1;
    }

    if (command == 'p') {
        print_game_statistics(
            *turns_taken,
            *step_count,
            *coins_collected,
            *score
        );
        return 0;
    }

    if (!gameplay_stage_3_2_is_turn_command(command)) {
        return 0;
    }

    (*turns_taken)++;

    if (gameplay_stage_3_2_is_movement_command(command)
        && !(command == 'w' && original_row == 0)) {
        g_last_move_used_tunnel = 0;
        gameplay_stage_2_2_process_movement_validation(
            board,
            player_row,
            player_col,
            command,
            &successful_move
        );
        *step_count += successful_move;

        if (successful_move) {
            gameplay_stage_3_3_collect_coin(
                board,
                *player_row,
                *player_col,
                score,
                coins_collected
            );
        }

        if (gameplay_stage_3_1_handle_collision(
                board,
                *player_row,
                *player_col,
                *score,
                target_score,
                *turns_taken,
                *step_count,
                *coins_collected
            )) {
            return 1;
        }
    }

    if (gameplay_stage_2_4_handle_game_won(
            board,
            *player_row,
            *player_col,
            *score,
            target_score,
            *turns_taken,
            *step_count,
            *coins_collected
        )) {
        return 1;
    }

    gameplay_stage_3_2_run_car_turn(board);

    if (gameplay_stage_3_1_handle_collision(
            board,
            *player_row,
            *player_col,
            *score,
            target_score,
            *turns_taken,
            *step_count,
            *coins_collected
        )) {
        return 1;
    }

    if (command == 'w' && original_row <= 6) {
        if (gameplay_stage_3_3_attempt_scroll(
                board,
                player_row,
                *player_col,
                score,
                target_score,
                turns_taken,
                step_count,
                coins_collected,
                coin_map,
                row_ids,
                original_row == 0,
                successful_move
            )) {
            return 1;
        }
    }
    else if (successful_move && g_last_move_used_tunnel && *player_row <= 6) {
        if (gameplay_stage_3_3_attempt_scroll(
                board,
                player_row,
                *player_col,
                score,
                target_score,
                turns_taken,
                step_count,
                coins_collected,
                coin_map,
                row_ids,
                0,
                1
            )) {
            return 1;
        }
    }

    print_board(
        board,
        *player_row,
        *player_col,
        *score,
        target_score
    );
    return 0;
}

void gameplay_stage_3_3_start_scrolling_mode(
    struct tile board[ROWS][COLS],
    int player_row,
    int player_col,
    int score,
    int target_score
) {
    int turns_taken = 0;
    int step_count = 0;
    int coins_collected = 0;
    int coin_map[ROWS][COLS] = {{0}};
    int row_ids[ROWS];
    char command;

    for (int row = 0; row < ROWS; row++) {
        row_ids[row] = row;
    }
    gameplay_stage_3_3_initialise_coin_map(board, coin_map);

    print_board(board, player_row, player_col, score, target_score);
    printf("============ Gameplay Phase =============\n");

    while (scanf(" %c", &command) == 1) {
        if (gameplay_stage_3_3_process_turn(
                board,
                &player_row,
                &player_col,
                &score,
                target_score,
                &turns_taken,
                &step_count,
                &coins_collected,
                coin_map,
                row_ids,
                command
            )) {
            return;
        }
    }
}
