#ifndef INCLUDE_H
#define INCLUDE_H

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int p1_score;
    int p2_score;
    int round;
    int total_rounds;
    char p1_choice;
    char p2_choice;
    gboolean p1_ready;
    gboolean p2_ready;
    gboolean game_started;
    gboolean round_completed;
} GameState;

typedef struct {
    GtkWidget *window;
    GtkWidget *main_box;
    GtkWidget *title_label;
    GtkWidget *round_label;
    GtkWidget *rules_label;
    GtkWidget *setup_frame;
    GtkWidget *rounds_label;
    GtkWidget *rounds_spinbutton;
    GtkWidget *p1_frame;
    GtkWidget *p2_frame;
    GtkWidget *p1_cooperate_btn;
    GtkWidget *p1_defect_btn;
    GtkWidget *p2_cooperate_btn;
    GtkWidget *p2_defect_btn;
    GtkWidget *p1_choice_label;
    GtkWidget *p2_choice_label;
    GtkWidget *result_label;
    GtkWidget *score_label;
    GtkWidget *next_round_btn;
    GtkWidget *start_btn;
    GtkWidget *final_result_label;
    GameState *game;
} AppWidgets;

extern AppWidgets *app_widgets;

void calculate_points(char p1, char p2, int* p1_points, int* p2_points);
void update_score_display();
void update_round_display();
void reset_round();
void check_round_complete();
void on_p1_cooperate_clicked(GtkWidget *widget, gpointer data);
void on_p1_defect_clicked(GtkWidget *widget, gpointer data);
void on_p2_cooperate_clicked(GtkWidget *widget, gpointer data);
void on_p2_defect_clicked(GtkWidget *widget, gpointer data);
void on_next_round_clicked(GtkWidget *widget, gpointer data);
void on_start_game_clicked(GtkWidget *widget, gpointer data);
void create_ui();
void init_game();

#endif