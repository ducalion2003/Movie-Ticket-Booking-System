#include <stdio.h>
#include <string.h>

#define MOVIES 3
#define SHOWTIMES 2
#define ROWS 5
#define COLS 10

// Base Prices based on row tier
#define PRICE_REGULAR 500.0  // Rows A-B
#define PRICE_PREMIUM 750.0  // Rows C-D
#define PRICE_VIP     1000.0 // Row E

// --- Data Structures ---
typedef struct {
    int isBooked;            // 0 = Available, 1 = Booked
    char customerName[50];   // Name of customer who booked
    double pricePaid;        // Final price paid for this seat
} Seat;

typedef struct {
    char time[20];
    Seat seats[ROWS][COLS];
    int totalTicketsSold;
    double totalRevenue;
} Showtime;

typedef struct {
    int id;
    char title[50];
    Showtime showtimes[SHOWTIMES];
} Movie;

// --- Global Data Storage ---
Movie movieData[MOVIES];

// --- Function Prototypes ---
void initData(void);
void displayMenu(void);
void menu(void);
void viewSeatMap(void);

// ==========================================
// Main Function
// ==========================================
int main()
{
    initData(); // Initialize movies, showtimes, and default seat grids
    menu();     // Call the main menu controller loop

    return 0;
}

// ==========================================
// Initialization Functions
// ==========================================
void initData(void)
{
    char *titles[MOVIES] = {"Odyssey", "Avengers: Doomsday", "Spider-Man: Brand New Day"};
    char *times[SHOWTIMES] = {"10:00 AM", "06:00 PM"};

    for (int i = 0; i < MOVIES; i++)
    {
        movieData[i].id = i + 1;
        strcpy(movieData[i].title, titles[i]);

        for (int j = 0; j < SHOWTIMES; j++)
        {
            strcpy(movieData[i].showtimes[j].time, times[j]);
            movieData[i].showtimes[j].totalTicketsSold = 0;
            movieData[i].showtimes[j].totalRevenue = 0.0;

            for (int r = 0; r < ROWS; r++)
            {
                for (int c = 0; c < COLS; c++)
                {
                    movieData[i].showtimes[j].seats[r][c].isBooked = 0;
                    movieData[i].showtimes[j].seats[r][c].customerName[0] = '\0';
                    movieData[i].showtimes[j].seats[r][c].pricePaid = 0.0;
                }
            }
        }
    }
}

// ==========================================
// Display Menu Function
// ==========================================
void displayMenu(void)
{
    printf("\n=====================================\n");
    printf("     MOVIE TICKET BOOKING SYSTEM\n");
    printf("=====================================\n");

    printf("1. View Showtimes\n");
    printf("2. View Seat Map\n");
    printf("3. Book a Seat\n");
    printf("4. Cancel Booking\n");
    printf("5. Search Booking\n");
    printf("6. Revenue Report\n");
    printf("7. Exit\n");
}

// ==========================================
// View Seat Map Function
// ==========================================
void viewSeatMap(void)
{
    int movieChoice, showtimeChoice;

    printf("\n--- SELECT MOVIE & SHOWTIME ---\n");
    for (int i = 0; i < MOVIES; i++)
    {
        printf("%d. %s\n", movieData[i].id, movieData[i].title);
    }

    printf("Select Movie (1-%d): ", MOVIES);
    if (scanf("%d", &movieChoice) != 1 || movieChoice < 1 || movieChoice > MOVIES)
    {
        printf("[ERROR] Invalid Movie selection!\n");
        while (getchar() != '\n'); // clear input buffer
        return;
    }

    printf("\nShowtimes:\n1. 10:00 AM\n2. 06:00 PM\n");
    printf("Select Showtime (1-%d): ", SHOWTIMES);
    if (scanf("%d", &showtimeChoice) != 1 || showtimeChoice < 1 || showtimeChoice > SHOWTIMES)
    {
        printf("[ERROR] Invalid Showtime selection!\n");
        while (getchar() != '\n'); // clear input buffer
        return;
    }

    int m = movieChoice - 1;
    int s = showtimeChoice - 1;
    Showtime *st = &movieData[m].showtimes[s];

    printf("\n==================================================\n");
    printf(" SEAT MAP: %s (%s)\n", movieData[m].title, st->time);
    printf(" Legend: [ . ] Free   [ X ] Booked\n");
    printf(" Pricing: Rows A-B: Regular (Rs.500) | Rows C-D: Premium (Rs.750) | Row E: VIP (Rs.1000)\n");
    printf("==================================================\n\n");

    printf("      ");
    for (int c = 1; c <= COLS; c++)
    {
        printf("%2d ", c);
    }
    printf("\n    +------------------------------+\n");

    for (int r = 0; r < ROWS; r++)
    {
        char rowLabel = 'A' + r;
        printf(" %c  |", rowLabel);

        for (int c = 0; c < COLS; c++)
        {
            if (st->seats[r][c].isBooked)
                printf("  X");
            else
                printf("  .");
        }
        printf("\n");
    }
    printf("    +------------------------------+\n");
}

// ==========================================
// Menu Control Handler
// ==========================================
void menu(void)
{
    int choice;

    do
    {
        displayMenu(); // Call display menu function

        printf("\nEnter Choice: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("\nInvalid Input! Please enter a number.\n");
            while (getchar() != '\n'); // clear buffer
            continue;
        }

        switch(choice)
        {
            case 1:
                printf("\nView Showtimes\n");
                break;

            case 2:
                viewSeatMap(); // Call View Seat Map function
                break;

            case 3:
                printf("\nBook a Seat\n");
                break;

            case 4:
                printf("\nCancel Booking\n");
                break;

            case 5:
                printf("\nSearch Booking\n");
                break;

            case 6:
                printf("\nRevenue Report\n");
                break;

            case 7:
                printf("\nThank You!\n");
                break;

            default:
                printf("\nInvalid Choice!\n");
        }

    } while(choice != 7);
}