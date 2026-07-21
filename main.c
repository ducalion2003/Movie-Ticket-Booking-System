#include <stdio.h>
#include <string.h>


int main()
{
    int choice;

    do
    {
        printf("\n=====================================\n");
        printf("   MOVIE TICKET BOOKING SYSTEM\n");
        printf("=====================================\n");

        printf("1. View Showtimes\n");
        printf("2. View Seat Map\n");
        printf("3. Book a Seat\n");
        printf("4. Cancel Booking\n");
        printf("5. Search Booking\n");
        printf("6. Revenue Report\n");
        printf("7. Exit\n");

        printf("\nEnter Choice : ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("\nView Showtimes\n");
                break;

            case 2:
                printf("\nView Seat Map\n");
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

    return 0;
}