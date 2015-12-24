import java.io.*;
import java.net.*;
import java.util.Scanner;
import java.util.Random;

public class Server {

	private static Integer port = 1234;
	private static Boolean quit = false;

	public static void main(String args[]) throws Exception {
		String c1response = "";
		String c2response = "";
		
		String c1input;
		String c2input;

		System.out.println("Welcome to Rock, Paper, Scissors.");
		Server.port = rand.nextInt((5000 - 1000) + 1) + 1000;

		ServerSocket socket = new ServerSocket(Server.port);

		while (1) {

		System.out.println("Now listening on port " + socket.getLocalPort());

		while (!Server.quit) {
		Socket client_1 = welcomeSocket.accept();
			if (client_1.isConnected()) {
				System.out.println("\nPlayer one (" + (client_1.getLocalAddress().toString()).substring(1) + ":"
						+ client_1.getLocalPort() + ") has joined ... waiting for player two ...");
			}
			DataOutputStream outClient_1 = new DataOutputStream(client_1.getOutputStream());
			BufferedReader inClient_1 = new BufferedReader(new InputStreamReader(client_1.getInputStream()));

			// Player two
			Socket client_2 = welcomeSocket.accept();
			if (client_2.isConnected()) {
				System.out.println("Player two (" + (client_2.getLocalAddress().toString()).substring(1) + ":"
						+ client_1.getLocalPort() + ") has joined ... lets start ...");
			}
			DataOutputStream outClient_2 = new DataOutputStream(client_2.getOutputStream());
			BufferedReader inClient_2 = new BufferedReader(new InputStreamReader(client_2.getInputStream()));

			// Get client inputs
			inputClient_1 = inClient_1.readLine();
			inputClient_2 = inClient_2.readLine();

			/**
			 * If the characters received from C1 and C2 are the same then the
			 * server sends back to both clients the string "DRAW".
			 */
			if (inputClient_1.equals(inputClient_2)) {
				resClient_1 = "Draw";
				resClient_2 = "Draw";
				System.out.println("It's a draw.");
			}
			/**
			 * If the server receives ’R’ from C1 and ’S’ from C2 it sends the
			 * string "YOU WIN" to C1 and the string "YOU LOSE" to C2.
			 */
			else if (inputClient_1.equals("R") && inputClient_2.equals("S")) {
				resClient_1 = "You win";
				resClient_2 = "You lose";
				System.out.println("Player one wins.");

			}
			/**
			 * If the server receives ’S’ from C1 and ’R’ from C2 it sends the
			 * string "YOU LOSE" to C1 and the string "YOU WIN" to C2.
			 */
			else if (inputClient_1.equals("S") && inputClient_2.equals("R")) {
				resClient_1 = "You lose";
				resClient_2 = "You win";
				System.out.println("Player two wins.");
			}
			/**
			 * If the server receives ’R’ from C1 and ’P’ from C2 it sends the
			 * string "YOU LOSE" to C1 and the string "YOU WIN" to C2.
			 */
			else if (inputClient_1.equals("R") && inputClient_2.equals("P")) {
				resClient_1 = "You lose";
				resClient_2 = "You win";
				System.out.println("Player two wins.");
			}
			/**
			 * If the server receives ’P’ from C1 and ’R’ from C2 it sends the
			 * string "YOU WIN" to C1 and the string "YOU LOSE" to C2.
			 */
			else if (inputClient_1.equals("P") && inputClient_2.equals("R")) {
				resClient_1 = "You win";
				resClient_2 = "You lose";
				System.out.println("Player one wins.");
			}
			/**
			 * If the server receives ’S’ from C1 and ’P’ from C2 it sends the
			 * string "YOU WIN" to C1 and the string "YOU LOSE" to C2.
			 */
			else if (inputClient_1.equals("S") && inputClient_2.equals("P")) {
				resClient_1 = "You win";
				resClient_2 = "You lose";
				System.out.println("Player one wins.");
			}
			/**
			 * If the server receives ’P’ from C1 and ’S’ from C2 it sends the
			 * string "YOU LOSE" to C1 and the string "YOU WIN" to C2.
			 */
			else if (inputClient_1.equals("P") && inputClient_2.equals("S")) {
				resClient_1 = "You lose";
				resClient_2 = "You win";
				System.out.println("Player two wins.");
			}
		}
	}
}
