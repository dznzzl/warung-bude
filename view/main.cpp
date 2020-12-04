#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "../controllers/controller.h"
#include "../controllers/validation.h"

int totalDish = 0, dishWidth = 0;

// menu Add Dish
void addDish() {
  // prompt user untuk input nama dish
  char name[255];
  do {
    printf("Insert the name of the dish [Lowercase letters]: ");
    scanf("%[^\n]", name); getchar();
  } while(!isValidDishName(name)); // validasi input
  if(strlen(name) > dishWidth) {
    dishWidth = strlen(name); // untuk menampung dish dengan nama terpanjang
  }
  // prompt user untuk input harga dish
  int price;
  do {
    printf("Insert the price of the dish [1000..50000]: ");
    scanf("%d", &price); getchar();
  } while(!isValidPrice(price)); // validasi input
  // prompt user untuk input stok atau quantity dari dish
  int qty;
  do {
    printf("Insert the quantity of the dish [1..999]: ");
    scanf("%d", &qty); getchar();
  } while(!isValidQty(qty)); // validasi input
  pushMid(name, price, qty); // insert sorted/priority queue berdasarkan quantity
  totalDish++; // untuk tracking jumlah dish yang ada
  printf("The dish has been added!\n");
  printf("Press enter to continue..."); getchar();
}

// menu Remove Dish
void removeDish() {
  if(displayDish(dishWidth + 2)) { // kalau ada menu, display
    // prompt user untuk input nama dish
    char name[255];
    do {
      printf("Insert dish's name to be deleted: ");
      scanf("%[^\n]", name); getchar();
    } while(!isValidDish(name)); // validasi input
    popMid(curr->qty); // diremove sesuai quantity
    printf("The dish has been removed!\n");
    printf("Press enter to continue..."); getchar();
  }
  else {
    return;
  }
}

// menu Add Customer
void addCustomer() {
  // prompt user untuk input nama customer
  char name[255];
  do {
    printf("Insert the customer's name [Without Space]: ");
    scanf("%[^\n]", name); getchar();
  } while(!isValidCustName(name)); // validasi input
  insert(name); // dihash pake djb2 dan dimasukin ke table
  printf("Customer has been added!\n");
  printf("Press enter to continue..."); getchar();
}

// menu Search Customer
void searchCustomer() {
  // prompt user untuk input nama customer yang ingin dicari
  char name[255];
  do {
    printf("Insert the customer's name to be searched: ");
    scanf("%[^\n]", name); getchar();
  } while(!isValidSearchName(name));
  (search(name)) ? printf("%s is present.\n", name) : printf("%s is not present.\n", name);
  printf("Press enter to continue..."); getchar();
}

// menu View Warteg
void viewWarteg() {
  puts("Customer's List\n");
  view(); // display isi dari index table yang tidak null
  printf("\nPress enter to continue..."); getchar();
}

// menu Order
void order() {
  // prompt user untuk input nama customer
  char name[255];
  do {
    printf("Insert the customer's name: ");
    scanf("%[^\n]", name); getchar();
  } while(!search(name)); // validasi input
  // prompt user untuk input jumlah dish yang diinginkan
  int amt;
  do {
    printf("Insert the amount of dish: ");
    scanf("%d", &amt); getchar();
  } while(!isValidAmt(amt, totalDish)); // validasi input
  for(int i = 1; i <= amt; i++) { // loop sesuai banyak dish yang diinginkan
    // prompt user untuk pilihan dish yang diinginkan serta jumlah masing-masing dish
    int qty, price;
    char dishName[255];
    do {
      printf("[%d] Insert the dish's name and quantity: ", i);
      scanf("%[^x]x%d", dishName, qty); getchar();
      // retrieve dish pilihan dari list, dan update status dish
      curr = head;
      while(curr) {
        if(!strcmp(curr->name, name)) {
          price = curr->price;
          break;
        }
        curr = curr->next;
      }
      price *= qty;
    } while(!isValidOrder(dishName)); // hanya jika nama invalid, maka akan mengulang
    Customer *curr = getNode(name); // untuk mendapatkan node customer pada index dimana nama dihash
    insertOrder(curr, dishName, qty, price); // masukkan order ke list order di dalam list customer
    puts("Order success!");
    printf("Press enter to continue..."); getchar();
  }
}

// menu Payment
void payment() {
  // prompt user untuk input index yang ingin dicheckout
  int index;
  do {
    printf("Insert the customer's index: ");
    scanf("%d", &index); getchar();
  } while(!isValidIndex(index)); // validasi input 
  puts("");
  displayPayment(index); // display bon dari customer pada index tertentu
  printf("Press enter to continue..."); getchar();
}

// menu Exit
void splashScreen() {
  char c;
  puts("Please expand your terminal to full screen!");
  printf("Press enter to continue..."); getchar();
  cls();
  FILE *fp;
  fp = fopen("splash-screen.txt", "r"); // baca file berisi ascii art
  while(fscanf(fp, "%c", &c) != EOF) { // baca per char selagi belum EOF
    printf("%c", c); // sekalian diprint ke terminal setelah dibaca
  }
}

void mainMenu() {
  int input;
  do {
    cls();
    printf("System: %s\n", detectOS());
    time_t now;
    time(&now);
    printf("%s\n", ctime(&now));
    puts("1. Add Dish");
    puts("2. Remove Dish");
    puts("3. Add customer");
    puts("4. Search customer");
    puts("5. View Warteg");
    puts("6. Order");
    puts("7. Payment");
    puts("8. Exit warteg");
    printf(">> ");
    scanf("%d", &input); getchar();
    if(input == 1) {
      cls();
      addDish();
    }
    if(input == 2) {
      cls();
      removeDish();
    }
    if(input == 3) {
      cls();
      addCustomer();
    }
    if(input == 4) {
      cls();
      searchCustomer();
    }
    if(input == 5) {
      cls();
      viewWarteg();
    }
    if(input == 6) {
      cls();
      order();
    }
    if(input == 7) {
      cls();
      payment();
    }
    if(input == 8) {
      cls();
      splashScreen();
      break;
    }
  } while(input != 8);
}

int main() {
  mainMenu();
  return 0;
}