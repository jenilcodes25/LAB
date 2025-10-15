import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

public class DHCPClient {
    public static void main(String[] args) {
        try {
            DatagramSocket socket = new DatagramSocket();
            socket.setBroadcast(true);
            byte[] discover = "DHCP Discover".getBytes();

            // Send DHCP Discover
            DatagramPacket discoverPacket = new DatagramPacket(discover, discover.length, InetAddress.getByName("255.255.255.255"), 67);
            socket.send(discoverPacket);
            System.out.println("Sent DHCP Discover");

            // Receive DHCP Offer
            byte[] buffer = new byte[1024];
            DatagramPacket offerPacket = new DatagramPacket(buffer, buffer.length);
            socket.receive(offerPacket);

            String offerMessage = new String(offerPacket.getData(), 0, offerPacket.getLength());
            System.out.println("Received: " + offerMessage);

            // Close the socket
            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
