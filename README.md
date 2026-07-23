# Movie Ticket Booking System in C

A lightweight, terminal-based Movie Ticket Booking System written in C. This program allows users to view available showtimes, inspect interactive seat maps with dynamic tier-based pricing, book password-protected seats, cancel existing reservations, and search active bookings.

---

## 🌟 Features

* **Interactive Seat Map**: Real-time visual representation of available (`.`) and booked (`X`) seats.
* **Tier-Based & Discount Pricing**:
  * Row A–B: Regular (Rs. 500)
  * Row C–D: Premium (Rs. 750)
  * Row E: VIP (Rs. 1000)
  * Special category discounts for Students (10%) and Senior Citizens (20%).
  * Automatic 10% group discount applied when booking 4 or more seats in a single transaction.
* **Password-Protected Cancellation**: Requires the original booking password to cancel a seat, preventing unauthorized cancellations and processing accurate refunds.
* **Search Functionality**: Allows searching through active reservations by customer name or specific seat number (e.g., `A5`).
* **Input Validation**: Clean handling of invalid numeric selections, seat coordinates, and duplicate seat selections.

---

## 🛠️ Prerequisites

* A C compiler installed on your system:
  * **macOS / Linux**: `gcc` or `clang`
  * **Windows**: MinGW (`gcc`) or MSVC

---

## 🚀 Compilation & Running

### 1. Clone the Repository
```bash
git clone [https://github.com/ducalion2003/Movie-Ticket-Booking-System.git](https://github.com/ducalion2003/Movie-Ticket-Booking-System.git)
cd Movie-Ticket-Booking-System
