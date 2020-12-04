struct Dish {
  char name[255];
  int price, qty;
  Dish *next, *prev;
} *head, *tail, *curr;

struct Order {
  char name[255];
  int price, qty;
  Order *nextOrder, *prevOrder;
} *currOrder;

struct Customer {
  char name[255];
  Order *headOrder, *tailOrder;
  Customer *nextCust, *prevCust;
} *headCust[26], *tailCust[26], *currCust;