import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class Restaurant {
    
    public static void main(String[] args) {

        Map<String, Double> menu = new HashMap<>();
        menu.put("burger", 80.99);
        menu.put("pizza", 100.99);
        menu.put("fries", 30.99);
        menu.put("soda", 10.99);
        menu.put("samosa", 5.00);
        menu.put("pasta", 70.50);
        menu.put("vada pav", 4.00);
        menu.put("chai", 2.50);
        menu.put("biryani", 70.00);
        menu.put("gulab jamun", 3.00);
        menu.put("masala dosa", 30.00);
        menu.put("paneer tikka", 30.00);
        menu.put("lassi", 10.00);
        menu.put("jalebi", 10.50);
        menu.put("roti", 10.00);
        menu.put("dal", 10.50);
        menu.put("chole bhature", 80.00);
        menu.put("idli", 25.00);
        menu.put("sambar", 20.00);


        System.out.println("Welcome to our restaurant!");
        System.out.println("Here is our menu:");
        for (Map.Entry<String, Double> entry : menu.entrySet()) {
            System.out.println(entry.getKey() + ": $" + entry.getValue());
        }

        ArrayList<String> order = new ArrayList<>();
        double total = 0.0;

        Scanner input = new Scanner(System.in);
        String userOrder = "";

        while (true) {
            System.out.println("\nWhat do you want to order? (Type 'done' to finish)");
            userOrder = input.nextLine().toLowerCase();

            if (userOrder.equals("done")) {
                break;
            }

            if (menu.containsKey(userOrder)) {
                order.add(userOrder);
                total += menu.get(userOrder);
                System.out.println("Added " + userOrder + " to your order.");
            } else {
                System.out.println("Sorry, we don't have that item on the menu.");
            }
        }

        System.out.println("\nThank you for your order!");
        System.out.println("You ordered:");
        for (String item : order) {
            System.out.println("- " + item);
        }
        System.out.println(String.format("Your total is: $%.2f", total));

        input.close();
    }
}
