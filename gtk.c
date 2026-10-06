#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100

typedef struct
{
    int rollNo;
    char name[50];
    char branch[30];
    char year[20];
    char phone[20];
    char email[60];

} Student;

Student students[MAX_STUDENTS];

int studentCount = 0;

GtkWidget *roll_entry;
GtkWidget *result_label;


/* Add sample student data */
void loadStudents()
{
    students[0].rollNo = 101;
    strcpy(students[0].name, "Rahul");
    strcpy(students[0].branch, "AI & ML");
    strcpy(students[0].year, "1st Year");
    strcpy(students[0].phone, "9876543210");
    strcpy(students[0].email, "rahul@gmail.com");

    students[1].rollNo = 102;
    strcpy(students[1].name, "Priya");
    strcpy(students[1].branch, "CSE");
    strcpy(students[1].year, "1st Year");
    strcpy(students[1].phone, "9876501234");
    strcpy(students[1].email, "priya@gmail.com");

    students[2].rollNo = 103;
    strcpy(students[2].name, "Arun");
    strcpy(students[2].branch, "ECE");
    strcpy(students[2].year, "2nd Year");
    strcpy(students[2].phone, "9123456789");
    strcpy(students[2].email, "arun@gmail.com");

    studentCount = 3;
}


/* Search student */
void search_student(GtkWidget *widget, gpointer data)
{
    const char *rollText;
    int roll;
    int found = 0;

    rollText = gtk_entry_get_text(GTK_ENTRY(roll_entry));

    if (strlen(rollText) == 0)
    {
        gtk_label_set_text(
            GTK_LABEL(result_label),
            "Please enter Roll Number."
        );

        return;
    }

    roll = atoi(rollText);

    for (int i = 0; i < studentCount; i++)
    {
        if (students[i].rollNo == roll)
        {
            char result[500];

            sprintf(
                result,
                "STUDENT FOUND\n\n"
                "Roll Number : %d\n"
                "Name        : %s\n"
                "Branch      : %s\n"
                "Year        : %s\n"
                "Phone       : %s\n"
                "Email       : %s",

                students[i].rollNo,
                students[i].name,
                students[i].branch,
                students[i].year,
                students[i].phone,
                students[i].email
            );

            gtk_label_set_text(
                GTK_LABEL(result_label),
                result
            );

            found = 1;
            break;
        }
    }

    if (!found)
    {
        gtk_label_set_text(
            GTK_LABEL(result_label),
            "Student not found!"
        );
    }
}


/* Clear search */
void clear_fields(GtkWidget *widget, gpointer data)
{
    gtk_entry_set_text(
        GTK_ENTRY(roll_entry),
        ""
    );

    gtk_label_set_text(
        GTK_LABEL(result_label),
        "Search result will appear here."
    );
}


/* Main window */
static void activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *grid;

    GtkWidget *title;
    GtkWidget *roll_label;

    GtkWidget *search_button;
    GtkWidget *clear_button;

    loadStudents();

    /* Create window */
    window = gtk_application_window_new(app);

    gtk_window_set_title(
        GTK_WINDOW(window),
        "Student Information Search"
    );

    gtk_window_set_default_size(
        GTK_WINDOW(window),
        500,
        400
    );

    gtk_window_set_position(
        GTK_WINDOW(window),
        GTK_WIN_POS_CENTER
    );


    /* Create grid */
    grid = gtk_grid_new();

    gtk_grid_set_row_spacing(
        GTK_GRID(grid),
        15
    );

    gtk_grid_set_column_spacing(
        GTK_GRID(grid),
        10
    );

    gtk_container_set_border_width(
        GTK_CONTAINER(grid),
        30
    );

    gtk_container_add(
        GTK_CONTAINER(window),
        grid
    );


    /* Title */
    title = gtk_label_new(
        "STUDENT INFORMATION SEARCH"
    );

    gtk_grid_attach(
        GTK_GRID(grid),
        title,
        0, 0,
        2, 1
    );


    /* Roll number label */
    roll_label = gtk_label_new(
        "Enter Roll Number:"
    );

    gtk_grid_attach(
        GTK_GRID(grid),
        roll_label,
        0, 1,
        1, 1
    );


    /* Roll number entry */
    roll_entry = gtk_entry_new();

    gtk_entry_set_placeholder_text(
        GTK_ENTRY(roll_entry),
        "Example: 101"
    );

    gtk_grid_attach(
        GTK_GRID(grid),
        roll_entry,
        1, 1,
        1, 1
    );


    /* Search button */
    search_button = gtk_button_new_with_label(
        "Search"
    );

    gtk_grid_attach(
        GTK_GRID(grid),
        search_button,
        0, 2,
        1, 1
    );

    g_signal_connect(
        search_button,
        "clicked",
        G_CALLBACK(search_student),
        NULL
    );


    /* Clear button */
    clear_button = gtk_button_new_with_label(
        "Clear"
    );

    gtk_grid_attach(
        GTK_GRID(grid),
        clear_button,
        1, 2,
        1, 1
    );

    g_signal_connect(
        clear_button,
        "clicked",
        G_CALLBACK(clear_fields),
        NULL
    );


    /* Result */
    result_label = gtk_label_new(
        "Search result will appear here."
    );

    gtk_label_set_xalign(
        GTK_LABEL(result_label),
        0.0
    );

    gtk_grid_attach(
        GTK_GRID(grid),
        result_label,
        0, 3,
        2, 1
    );


    gtk_widget_show_all(window);
}


/* Main */
int main(int argc, char **argv)
{
    GtkApplication *app;
    int status;

    app = gtk_application_new(
        "com.example.StudentSearch",
        G_APPLICATION_DEFAULT_FLAGS
    );

    g_signal_connect(
        app,
        "activate",
        G_CALLBACK(activate),
        NULL
    );

    status = g_application_run(
        G_APPLICATION(app),
        argc,
        argv
    );

    g_object_unref(app);

    return status;
}