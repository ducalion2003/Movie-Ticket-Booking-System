#include <stdio.h>
#include <string.h>
#include <ctype.h>

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
    char password[30];       // Password required for cancellation
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
void viewShowtimes(void);
void viewSeatMap(void);
void bookASeat(void);
void cancelBooking(void);
void searchBooking(void);
double calculatePrice(int row, int discountType, int totalSeatsBooked);

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
// Initialization & Utility Functions
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
                    movieData[i].showtimes[j].seats[r][c].password[0] = '\0';
                    movieData[i].showtimes[j].seats[r][c].pricePaid = 0.0;
                }
            }
        }
    }
}

double calculatePrice(int row, int discountType, int totalSeatsBooked)
{
    double basePrice = 0.0;

    // Base pricing: Rows A-B (Regular), C-D (Premium), E (VIP)
    if (row == 0 || row == 1)
        basePrice = PRICE_REGULAR;
    else if (row == 2 || row == 3)
        basePrice = PRICE_PREMIUM;
    else if (row == 4)
        basePrice = PRICE_VIP;

    double finalPrice = basePrice;

    // Apply category discount (1 = Standard/0%, 2 = Student/10%, 3 = Senior/20%)
    if (discountType == 2)
        finalPrice -= (basePrice * 0.10);
    else if (discountType == 3)
        finalPrice -= (basePrice * 0.20);

    // Apply 10% group discount if 4 or more seats are booked in a single transaction
    if (totalSeatsBooked >= 4)
        finalPrice -= (basePrice * 0.10);

    return finalPrice;
}

// ==========================================
// Menu UI Functions
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
// 1. View Showtimes Function
// ==========================================
void viewShowtimes(void)
{
    printf("\n==================================================\n");
    printf("               AVAILABLE SHOWTIMES                \n");
    printf("==================================================\n");

    for (int i = 0; i < MOVIES; i++)
    {
        printf("Movie %d: %s\n", movieData[i].id, movieData[i].title);
        printf("Showtimes: ");

        for (int j = 0; j < SHOWTIMES; j++)
        {
            printf("[%s]", movieData[i].showtimes[j].time);
            if (j < SHOWTIMES - 1)
            {
                printf(" , ");
            }
        }
        printf("\n--------------------------------------------------\n");
    }
}

// ==========================================
// 2. View Seat Map Function
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
// 3. Book a Seat Function
// ==========================================
void bookASeat(void)
{
    int movieChoice, showtimeChoice, numSeats, discountType;
    char name[50];
    char pwd[30];

    printf("\n--- SELECT MOVIE & SHOWTIME ---\n");
    for (int i = 0; i < MOVIES; i++)
    {
        printf("%d. %s\n", movieData[i].id, movieData[i].title);
    }

    printf("Select Movie (1-%d): ", MOVIES);
    if (scanf("%d", &movieChoice) != 1 || movieChoice < 1 || movieChoice > MOVIES)
    {
        printf("[ERROR] Invalid Movie selection!\n");
        while (getchar() != '\n');
        return;
    }

    printf("\nShowtimes:\n1. 10:00 AM\n2. 06:00 PM\n");
    printf("Select Showtime (1-%d): ", SHOWTIMES);
    if (scanf("%d", &showtimeChoice) != 1 || showtimeChoice < 1 || showtimeChoice > SHOWTIMES)
    {
        printf("[ERROR] Invalid Showtime selection!\n");
        while (getchar() != '\n');
        return;
    }

    Showtime *st = &movieData[movieChoice - 1].showtimes[showtimeChoice - 1];

    printf("\nHow many seats do you want to book?: ");
    if (scanf("%d", &numSeats) != 1 || numSeats <= 0 || numSeats > (ROWS * COLS))
    {
        printf("[ERROR] Invalid number of seats!\n");
        while (getchar() != '\n');
        return;
    }

    // Clean remaining trailing newline from buffer
    getchar();

    printf("Enter Customer Name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // strip trailing newline

    printf("Set a Password for Cancellation: ");
    fgets(pwd, sizeof(pwd), stdin);
    pwd[strcspn(pwd, "\n")] = '\0'; // strip trailing newline

    if (strlen(pwd) == 0)
    {
        printf("[ERROR] Password cannot be empty!\n");
        return;
    }

    printf("\nSelect Category Discount:\n");
    printf("1. Regular / Standard (0%% discount)\n");
    printf("2. Student (10%% discount)\n");
    printf("3. Senior Citizen (20%% discount)\n");
    printf("Enter Choice (1-3): ");
    if (scanf("%d", &discountType) != 1 || discountType < 1 || discountType > 3)
    {
        printf("[WARNING] Invalid discount choice. Defaulting to Regular Category.\n");
        discountType = 1;
    }

    int targetRows[ROWS * COLS];
    int targetCols[ROWS * COLS];

    for (int i = 0; i < numSeats; i++)
    {
        char rowChar;
        int colNum;

        while (1)
        {
            printf("\nEnter Seat %d of %d (e.g., A 5 or C 10): ", i + 1, numSeats);
            if (scanf(" %c %d", &rowChar, &colNum) != 2)
            {
                printf("[ERROR] Invalid seat input format! Try again.\n");
                while (getchar() != '\n');
                continue;
            }

            rowChar = toupper(rowChar);
            int r = rowChar - 'A';
            int c = colNum - 1;

            // Range validation
            if (r < 0 || r >= ROWS || c < 0 || c >= COLS)
            {
                printf("[ERROR] Seat out of range! Rows are A-E and Seats are 1-10.\n");
                continue;
            }

            // Availability validation
            if (st->seats[r][c].isBooked)
            {
                printf("[ERROR] Seat %c%d is already taken! Pick a different seat.\n", rowChar, colNum);
                continue;
            }

            // Duplicate checks in current batch
            int isDuplicate = 0;
            for (int k = 0; k < i; k++)
            {
                if (targetRows[k] == r && targetCols[k] == c)
                {
                    isDuplicate = 1;
                    break;
                }
            }
            if (isDuplicate)
            {
                printf("[ERROR] You already selected seat %c%d in this transaction!\n", rowChar, colNum);
                continue;
            }

            targetRows[i] = r;
            targetCols[i] = c;
            break;
        }
    }

    // Processing & Calculations
    double totalBill = 0.0;
    printf("\n=====================================\n");
    printf("          BOOKING CONFIRMATION       \n");
    printf("=====================================\n");
    printf("Customer Name: %s\n", name);
    printf("Movie: %s (%s)\n", movieData[movieChoice - 1].title, st->time);
    printf("-------------------------------------\n");

    for (int i = 0; i < numSeats; i++)
    {
        int r = targetRows[i];
        int c = targetCols[i];

        double seatPrice = calculatePrice(r, discountType, numSeats);

        // Update grid state and recording metrics
        st->seats[r][c].isBooked = 1;
        strcpy(st->seats[r][c].customerName, name);
        strcpy(st->seats[r][c].password, pwd);
        st->seats[r][c].pricePaid = seatPrice;

        st->totalTicketsSold++;
        st->totalRevenue += seatPrice;
        totalBill += seatPrice;

        printf("Seat %c%d : Price Paid = Rs. %.2f\n", 'A' + r, c + 1, seatPrice);
    }

    if (numSeats >= 4)
    {
        printf("* Additional 10%% Group Discount Applied (4+ seats booked)!\n");
    }

    printf("-------------------------------------\n");
    printf("TOTAL PAID : Rs. %.2f\n", totalBill);
    printf("=====================================\n");
}

// ==========================================
// 4. Cancel Booking Function (With Password Security)
// ==========================================
void cancelBooking(void)
{
    int movieChoice, showtimeChoice;
    char rowChar;
    int colNum;
    char enteredPwd[30];

    printf("\n--- CANCEL BOOKING ---\n");
    for (int i = 0; i < MOVIES; i++)
    {
        printf("%d. %s\n", movieData[i].id, movieData[i].title);
    }

    printf("Select Movie (1-%d): ", MOVIES);
    if (scanf("%d", &movieChoice) != 1 || movieChoice < 1 || movieChoice > MOVIES)
    {
        printf("[ERROR] Invalid Movie selection!\n");
        while (getchar() != '\n');
        return;
    }

    printf("\nShowtimes:\n1. 10:00 AM\n2. 06:00 PM\n");
    printf("Select Showtime (1-%d): ", SHOWTIMES);
    if (scanf("%d", &showtimeChoice) != 1 || showtimeChoice < 1 || showtimeChoice > SHOWTIMES)
    {
        printf("[ERROR] Invalid Showtime selection!\n");
        while (getchar() != '\n');
        return;
    }

    Showtime *st = &movieData[movieChoice - 1].showtimes[showtimeChoice - 1];

    printf("\nEnter Seat to Cancel (e.g., A 5 or C 10): ");
    if (scanf(" %c %d", &rowChar, &colNum) != 2)
    {
        printf("[ERROR] Invalid seat format!\n");
        while (getchar() != '\n');
        return;
    }

    rowChar = toupper(rowChar);
    int r = rowChar - 'A';
    int c = colNum - 1;

    // Check row and column boundaries
    if (r < 0 || r >= ROWS || c < 0 || c >= COLS)
    {
        printf("[ERROR] Seat out of range! Rows are A-E and Seats are 1-10.\n");
        return;
    }

    // Check if the seat is actually booked
    if (!st->seats[r][c].isBooked)
    {
        printf("[ERROR] Seat %c%d is not currently booked.\n", rowChar, colNum);
        return;
    }

    // Password Verification
    getchar(); // Clear trailing newline
    printf("Enter Password for %s's Booking: ", st->seats[r][c].customerName);
    fgets(enteredPwd, sizeof(enteredPwd), stdin);
    enteredPwd[strcspn(enteredPwd, "\n")] = '\0'; // strip trailing newline

    if (strcmp(st->seats[r][c].password, enteredPwd) != 0)
    {
        printf("\n=====================================\n");
        printf(" [ERROR] INCORRECT PASSWORD!\n");
        printf(" Access Denied: Cancellation aborted.\n");
        printf("=====================================\n");
        return;
    }

    // Perform refund and reset seat data
    double refundedAmount = st->seats[r][c].pricePaid;
    st->seats[r][c].isBooked = 0;
    st->seats[r][c].customerName[0] = '\0';
    st->seats[r][c].password[0] = '\0';
    st->seats[r][c].pricePaid = 0.0;

    // Update global metrics
    st->totalTicketsSold--;
    st->totalRevenue -= refundedAmount;

    printf("\n=====================================\n");
    printf("          CANCELLATION SUCCESS       \n");
    printf("=====================================\n");
    printf("Seat %c%d has been successfully canceled.\n", rowChar, colNum);
    printf("Refund Amount: Rs. %.2f\n", refundedAmount);
    printf("=====================================\n");
}

// ==========================================
// 5. Search Booking Function
// ==========================================
void searchBooking(void)
{
    char searchTerm[50];

    printf("\n--- SEARCH BOOKINGS ---\n");
    getchar(); // Clear remaining newline in input buffer
    printf("Enter Customer Name or Seat Number (e.g., 'John' or 'A5'): ");
    fgets(searchTerm, sizeof(searchTerm), stdin);
    searchTerm[strcspn(searchTerm, "\n")] = '\0'; // Remove newline

    if (strlen(searchTerm) == 0)
    {
        printf("[ERROR] Search query cannot be empty!\n");
        return;
    }

    int foundCount = 0;

    printf("\n=================================================================================\n");
    printf("                                  SEARCH RESULTS                                 \n");
    printf("=================================================================================\n");

    for (int i = 0; i < MOVIES; i++)
    {
        for (int j = 0; j < SHOWTIMES; j++)
        {
            Showtime *st = &movieData[i].showtimes[j];

            for (int r = 0; r < ROWS; r++)
            {
                for (int c = 0; c < COLS; c++)
                {
                    if (st->seats[r][c].isBooked)
                    {
                        char seatCode[10];
                        snprintf(seatCode, sizeof(seatCode), "%c%d", 'A' + r, c + 1);

                        // Match against customer name OR specific seat code
                        if (strstr(st->seats[r][c].customerName, searchTerm) != NULL ||
                            strcmp(seatCode, searchTerm) == 0)
                        {
                            printf("Movie   : %s\n", movieData[i].title);
                            printf("Time    : %s\n", st->time);
                            printf("Seat    : %s\n", seatCode);
                            printf("Customer: %s\n", st->seats[r][c].customerName);
                            printf("Paid    : Rs. %.2f\n", st->seats[r][c].pricePaid);
                            printf("---------------------------------------------------------------------------------\n");
                            foundCount++;
                        }
                    }
                }
            }
        }
    }

    if (foundCount == 0)
    {
        printf("No active bookings found matching '%s'.\n", searchTerm);
        printf("=================================================================================\n");
    }
    else
    {
        printf("Total matches found: %d\n", foundCount);
        printf("=================================================================================\n");
    }
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
                viewShowtimes(); // Call the newly integrated function
                break;

            case 2:
                viewSeatMap(); // Call View Seat Map function
                break;

            case 3:
                bookASeat();   // Call Book a Seat function
                break;

            case 4:
                cancelBooking(); // Call Cancel Booking function
                break;

            case 5:
                searchBooking(); // Call Search Booking function
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
