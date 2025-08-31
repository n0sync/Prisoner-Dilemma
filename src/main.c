#include "include.h"

AppWidgets *app_widgets;

void calculate_points(char p1, char p2, int* p1_points, int* p2_points) {
    if (p1 == 'C' && p2 == 'C') {
        *p1_points = 3;
        *p2_points = 3;
    } else if (p1 == 'D' && p2 == 'D') {
        *p1_points = 1;
        *p2_points = 1;
    } else if (p1 == 'C' && p2 == 'D') {
        *p1_points = 0;
        *p2_points = 5;
    } else if (p1 == 'D' && p2 == 'C') {
        *p1_points = 5;
        *p2_points = 0;
    } else {
        *p1_points = 0;
        *p2_points = 0;
    }
}

void update_score_display() {
    char score_text[200];
    snprintf(score_text, sizeof(score_text), 
             "<b>SCORES:</b>\nPlayer 1: %d\nPlayer 2: %d", 
             app_widgets->game->p1_score, app_widgets->game->p2_score);
    gtk_label_set_markup(GTK_LABEL(app_widgets->score_label), score_text);
}

void update_round_display() {
    char round_text[100];
    snprintf(round_text, sizeof(round_text), 
             "<b>Round %d of %d</b>", 
             app_widgets->game->round + 1, app_widgets->game->total_rounds);
    gtk_label_set_markup(GTK_LABEL(app_widgets->round_label), round_text);
}

void reset_round() {
    app_widgets->game->p1_ready = FALSE;
    app_widgets->game->p2_ready = FALSE;
    app_widgets->game->round_completed = FALSE;
    
    gtk_label_set_text(GTK_LABEL(app_widgets->p1_choice_label), "Waiting for choice...");
    gtk_label_set_text(GTK_LABEL(app_widgets->p2_choice_label), "Waiting for choice...");
    gtk_label_set_text(GTK_LABEL(app_widgets->result_label), "");
    
    gtk_widget_set_sensitive(app_widgets->p1_cooperate_btn, TRUE);
    gtk_widget_set_sensitive(app_widgets->p1_defect_btn, TRUE);
    gtk_widget_set_sensitive(app_widgets->p2_cooperate_btn, TRUE);
    gtk_widget_set_sensitive(app_widgets->p2_defect_btn, TRUE);
    gtk_widget_set_sensitive(app_widgets->next_round_btn, FALSE);
}

void check_round_complete() {
    if (app_widgets->game->p1_ready && app_widgets->game->p2_ready && !app_widgets->game->round_completed) {
        app_widgets->game->round_completed = TRUE;
        
        int p1_points, p2_points;
        calculate_points(app_widgets->game->p1_choice, app_widgets->game->p2_choice, &p1_points, &p2_points);
        
        app_widgets->game->p1_score += p1_points;
        app_widgets->game->p2_score += p2_points;
        
        char p1_text[50], p2_text[50];
        snprintf(p1_text, sizeof(p1_text), "Choice: %s", 
                 app_widgets->game->p1_choice == 'C' ? "Cooperate" : "Defect");
        snprintf(p2_text, sizeof(p2_text), "Choice: %s", 
                 app_widgets->game->p2_choice == 'C' ? "Cooperate" : "Defect");
        
        gtk_label_set_text(GTK_LABEL(app_widgets->p1_choice_label), p1_text);
        gtk_label_set_text(GTK_LABEL(app_widgets->p2_choice_label), p2_text);
        
        char result_text[200];
        snprintf(result_text, sizeof(result_text), 
                 "<b>Round Result:</b>\nPlayer 1: +%d points\nPlayer 2: +%d points", 
                 p1_points, p2_points);
        gtk_label_set_markup(GTK_LABEL(app_widgets->result_label), result_text);
        
        update_score_display();
        
        gtk_widget_set_sensitive(app_widgets->p1_cooperate_btn, FALSE);
        gtk_widget_set_sensitive(app_widgets->p1_defect_btn, FALSE);
        gtk_widget_set_sensitive(app_widgets->p2_cooperate_btn, FALSE);
        gtk_widget_set_sensitive(app_widgets->p2_defect_btn, FALSE);
        
        if (app_widgets->game->round + 1 >= app_widgets->game->total_rounds) {
            char final_text[200];
            if (app_widgets->game->p1_score > app_widgets->game->p2_score)
                snprintf(final_text, sizeof(final_text), "<b><span color='green'>GAME OVER - Player 1 Wins!</span></b>");
            else if (app_widgets->game->p2_score > app_widgets->game->p1_score)
                snprintf(final_text, sizeof(final_text), "<b><span color='green'>GAME OVER - Player 2 Wins!</span></b>");
            else
                snprintf(final_text, sizeof(final_text), "<b><span color='blue'>GAME OVER - It's a Tie!</span></b>");
            
            gtk_label_set_markup(GTK_LABEL(app_widgets->final_result_label), final_text);
            gtk_widget_hide(app_widgets->next_round_btn);
        } else {
            gtk_widget_set_sensitive(app_widgets->next_round_btn, TRUE);
            gtk_widget_show(app_widgets->next_round_btn);
        }
    }
}

void on_p1_cooperate_clicked(GtkWidget *widget, gpointer data) {
    if (!app_widgets->game->p1_ready && !app_widgets->game->round_completed) {
        app_widgets->game->p1_choice = 'C';
        app_widgets->game->p1_ready = TRUE;
        gtk_label_set_text(GTK_LABEL(app_widgets->p1_choice_label), "Choice made!");
        check_round_complete();
    }
}

void on_p1_defect_clicked(GtkWidget *widget, gpointer data) {
    if (!app_widgets->game->p1_ready && !app_widgets->game->round_completed) {
        app_widgets->game->p1_choice = 'D';
        app_widgets->game->p1_ready = TRUE;
        gtk_label_set_text(GTK_LABEL(app_widgets->p1_choice_label), "Choice made!");
        check_round_complete();
    }
}

void on_p2_cooperate_clicked(GtkWidget *widget, gpointer data) {
    if (!app_widgets->game->p2_ready && !app_widgets->game->round_completed) {
        app_widgets->game->p2_choice = 'C';
        app_widgets->game->p2_ready = TRUE;
        gtk_label_set_text(GTK_LABEL(app_widgets->p2_choice_label), "Choice made!");
        check_round_complete();
    }
}

void on_p2_defect_clicked(GtkWidget *widget, gpointer data) {
    if (!app_widgets->game->p2_ready && !app_widgets->game->round_completed) {
        app_widgets->game->p2_choice = 'D';
        app_widgets->game->p2_ready = TRUE;
        gtk_label_set_text(GTK_LABEL(app_widgets->p2_choice_label), "Choice made!");
        check_round_complete();
    }
}

void on_next_round_clicked(GtkWidget *widget, gpointer data) {
    app_widgets->game->round++;
    reset_round();
    update_round_display();
}

void on_start_game_clicked(GtkWidget *widget, gpointer data) {
    app_widgets->game->total_rounds = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(app_widgets->rounds_spinbutton));
    
    app_widgets->game->game_started = TRUE;
    gtk_widget_hide(app_widgets->setup_frame);
    gtk_widget_hide(app_widgets->start_btn);
    gtk_widget_show(app_widgets->round_label);
    gtk_widget_show(app_widgets->p1_frame);
    gtk_widget_show(app_widgets->p2_frame);
    gtk_widget_show(app_widgets->score_label);
    reset_round();
    update_round_display();
    update_score_display();
}

void create_ui() {
    app_widgets->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(app_widgets->window), "Prisoner's Dilemma");
    gtk_window_set_default_size(GTK_WINDOW(app_widgets->window), 600, 500);
    gtk_container_set_border_width(GTK_CONTAINER(app_widgets->window), 10);
    
    app_widgets->main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(app_widgets->window), app_widgets->main_box);
    
    app_widgets->title_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(app_widgets->title_label), 
                        "<span size='x-large'><b>PRISONER'S DILEMMA</b></span>");
    gtk_label_set_justify(GTK_LABEL(app_widgets->title_label), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(app_widgets->main_box), app_widgets->title_label, FALSE, FALSE, 0);
    
    app_widgets->rules_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(app_widgets->rules_label),
                        "<b>RULES:</b>\n"
                        "• Both Cooperate: 3 points each\n"
                        "• Both Defect: 1 point each\n"
                        "• One Cooperates, One Defects: Defector gets 5, Cooperator gets 0");
    gtk_label_set_justify(GTK_LABEL(app_widgets->rules_label), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(app_widgets->main_box), app_widgets->rules_label, FALSE, FALSE, 0);
    
    app_widgets->setup_frame = gtk_frame_new("Game Setup");
    gtk_box_pack_start(GTK_BOX(app_widgets->main_box), app_widgets->setup_frame, FALSE, FALSE, 0);
    
    GtkWidget *setup_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_container_add(GTK_CONTAINER(app_widgets->setup_frame), setup_box);
    gtk_container_set_border_width(GTK_CONTAINER(setup_box), 10);
    
    app_widgets->rounds_label = gtk_label_new("Number of rounds:");
    gtk_box_pack_start(GTK_BOX(setup_box), app_widgets->rounds_label, FALSE, FALSE, 0);
    
    GtkAdjustment *adjustment = gtk_adjustment_new(5, 1, 20, 1, 1, 0);
    app_widgets->rounds_spinbutton = gtk_spin_button_new(adjustment, 1, 0);
    gtk_box_pack_start(GTK_BOX(setup_box), app_widgets->rounds_spinbutton, FALSE, FALSE, 0);
    
    app_widgets->round_label = gtk_label_new("");
    gtk_label_set_justify(GTK_LABEL(app_widgets->round_label), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(app_widgets->main_box), app_widgets->round_label, FALSE, FALSE, 0);
    
    GtkWidget *players_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    gtk_box_pack_start(GTK_BOX(app_widgets->main_box), players_box, TRUE, TRUE, 0);
    
    app_widgets->p1_frame = gtk_frame_new("Player 1");
    gtk_box_pack_start(GTK_BOX(players_box), app_widgets->p1_frame, TRUE, TRUE, 0);
    
    GtkWidget *p1_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(app_widgets->p1_frame), p1_box);
    gtk_container_set_border_width(GTK_CONTAINER(p1_box), 10);
    
    app_widgets->p1_cooperate_btn = gtk_button_new_with_label("Cooperate");
    app_widgets->p1_defect_btn = gtk_button_new_with_label("Defect");
    app_widgets->p1_choice_label = gtk_label_new("Waiting for choice...");
    
    gtk_box_pack_start(GTK_BOX(p1_box), app_widgets->p1_cooperate_btn, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(p1_box), app_widgets->p1_defect_btn, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(p1_box), app_widgets->p1_choice_label, FALSE, FALSE, 0);
    
    app_widgets->p2_frame = gtk_frame_new("Player 2");
    gtk_box_pack_start(GTK_BOX(players_box), app_widgets->p2_frame, TRUE, TRUE, 0);
    
    GtkWidget *p2_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(app_widgets->p2_frame), p2_box);
    gtk_container_set_border_width(GTK_CONTAINER(p2_box), 10);
    
    app_widgets->p2_cooperate_btn = gtk_button_new_with_label("Cooperate");
    app_widgets->p2_defect_btn = gtk_button_new_with_label("Defect");
    app_widgets->p2_choice_label = gtk_label_new("Waiting for choice...");
    
    gtk_box_pack_start(GTK_BOX(p2_box), app_widgets->p2_cooperate_btn, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(p2_box), app_widgets->p2_defect_btn, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(p2_box), app_widgets->p2_choice_label, FALSE, FALSE, 0);
    
    app_widgets->result_label = gtk_label_new("");
    gtk_label_set_justify(GTK_LABEL(app_widgets->result_label), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(app_widgets->main_box), app_widgets->result_label, FALSE, FALSE, 0);
    
    app_widgets->score_label = gtk_label_new("");
    gtk_label_set_justify(GTK_LABEL(app_widgets->score_label), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(app_widgets->main_box), app_widgets->score_label, FALSE, FALSE, 0);
    
    app_widgets->start_btn = gtk_button_new_with_label("Start Game");
    gtk_box_pack_start(GTK_BOX(app_widgets->main_box), app_widgets->start_btn, FALSE, FALSE, 0);
    
    app_widgets->next_round_btn = gtk_button_new_with_label("Next Round");
    gtk_box_pack_start(GTK_BOX(app_widgets->main_box), app_widgets->next_round_btn, FALSE, FALSE, 0);
    
    app_widgets->final_result_label = gtk_label_new("");
    gtk_label_set_justify(GTK_LABEL(app_widgets->final_result_label), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(app_widgets->main_box), app_widgets->final_result_label, FALSE, FALSE, 0);
    
    gtk_widget_hide(app_widgets->round_label);
    gtk_widget_hide(app_widgets->p1_frame);
    gtk_widget_hide(app_widgets->p2_frame);
    gtk_widget_hide(app_widgets->score_label);
    gtk_widget_hide(app_widgets->next_round_btn);
    
    g_signal_connect(app_widgets->p1_cooperate_btn, "clicked", 
                     G_CALLBACK(on_p1_cooperate_clicked), NULL);
    g_signal_connect(app_widgets->p1_defect_btn, "clicked", 
                     G_CALLBACK(on_p1_defect_clicked), NULL);
    g_signal_connect(app_widgets->p2_cooperate_btn, "clicked", 
                     G_CALLBACK(on_p2_cooperate_clicked), NULL);
    g_signal_connect(app_widgets->p2_defect_btn, "clicked", 
                     G_CALLBACK(on_p2_defect_clicked), NULL);
    g_signal_connect(app_widgets->next_round_btn, "clicked", 
                     G_CALLBACK(on_next_round_clicked), NULL);
    g_signal_connect(app_widgets->start_btn, "clicked", 
                     G_CALLBACK(on_start_game_clicked), NULL);
    g_signal_connect(app_widgets->window, "destroy", 
                     G_CALLBACK(gtk_main_quit), NULL);
}

void init_game() {
    app_widgets->game = g_malloc(sizeof(GameState));
    app_widgets->game->p1_score = 0;
    app_widgets->game->p2_score = 0;
    app_widgets->game->round = 0;
    app_widgets->game->total_rounds = 5;
    app_widgets->game->p1_ready = FALSE;
    app_widgets->game->p2_ready = FALSE;
    app_widgets->game->game_started = FALSE;
    app_widgets->game->round_completed = FALSE;
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    
    app_widgets = g_malloc(sizeof(AppWidgets));
    init_game();
    create_ui();
    
    gtk_widget_show_all(app_widgets->window);
    
    gtk_widget_hide(app_widgets->round_label);
    gtk_widget_hide(app_widgets->p1_frame);
    gtk_widget_hide(app_widgets->p2_frame);
    gtk_widget_hide(app_widgets->score_label);
    gtk_widget_hide(app_widgets->next_round_btn);
    
    gtk_main();
    
    g_free(app_widgets->game);
    g_free(app_widgets);
    
    return 0;
}