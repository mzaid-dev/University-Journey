
#include <pcap.h>
#include <iostream>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>

using namespace std;

// Function to process each captured packet
void packetHandler(
    u_char *userData,
    const struct pcap_pkthdr* pkthdr,
    const u_char* packet
)
{
    // Check Ethernet header length
    if (pkthdr->caplen < 14)
        return;

    // Skip the 14-byte Ethernet header
    struct ip* ipHeader;

    ipHeader = (struct ip*)(packet + 14);

    // Check IPv4 packet
    if (ipHeader->ip_v != 4)
        return;

    int ipHeaderLength = ipHeader->ip_hl * 4;

    // Validate IP header length
    if (ipHeaderLength < 20 ||
        pkthdr->caplen < 14 + ipHeaderLength)
        return;

    cout << "\n---- Packet Captured ----" << endl;

    cout << "Source IP: "
         << inet_ntoa(ipHeader->ip_src) << endl;

    cout << "Destination IP: "
         << inet_ntoa(ipHeader->ip_dst) << endl;

    cout << "Protocol: "
         << (int)ipHeader->ip_p << endl;


    // ================= TCP PACKET =================

    if (ipHeader->ip_p == IPPROTO_TCP)
    {
        if (pkthdr->caplen < 14 + ipHeaderLength + 20)
            return;

        cout << "TCP Packet Detected" << endl;

        struct tcphdr* tcpHeader;

        tcpHeader = (struct tcphdr*)(
            packet + 14 + ipHeaderLength
        );

        // -------- macOS VERSION (ACTIVE) --------

        cout << "Source Port: "
             << ntohs(tcpHeader->th_sport) << endl;

        cout << "Destination Port: "
             << ntohs(tcpHeader->th_dport) << endl;


        // -------- UBUNTU VERSION (ALTERNATIVE) --------

        /*
        cout << "Source Port: "
             << ntohs(tcpHeader->source) << endl;

        cout << "Destination Port: "
             << ntohs(tcpHeader->dest) << endl;
        */


        // Check HTTP port 80 (macOS)

        if (ntohs(tcpHeader->th_dport) == 80 ||
            ntohs(tcpHeader->th_sport) == 80)
        {
            cout << "HTTP Packet Detected (Port 80)" << endl;
        }

        // UBUNTU HTTP alternative:
        /*
        if (ntohs(tcpHeader->dest) == 80 ||
            ntohs(tcpHeader->source) == 80)
        {
            cout << "HTTP Packet Detected (Port 80)" << endl;
        }
        */
    }


    // ================= UDP PACKET =================

    else if (ipHeader->ip_p == IPPROTO_UDP)
    {
        if (pkthdr->caplen < 14 + ipHeaderLength + 8)
            return;

        cout << "UDP Packet Detected" << endl;

        struct udphdr* udpHeader;

        udpHeader = (struct udphdr*)(
            packet + 14 + ipHeaderLength
        );


        // -------- macOS VERSION (ACTIVE) --------

        cout << "Source Port: "
             << ntohs(udpHeader->uh_sport) << endl;

        cout << "Destination Port: "
             << ntohs(udpHeader->uh_dport) << endl;


        // -------- UBUNTU VERSION (ALTERNATIVE) --------

        /*
        cout << "Source Port: "
             << ntohs(udpHeader->source) << endl;

        cout << "Destination Port: "
             << ntohs(udpHeader->dest) << endl;
        */
    }
}


// ================= MAIN FUNCTION =================

int main()
{
    char errbuf[PCAP_ERRBUF_SIZE];

    pcap_if_t *alldevs = nullptr;
    pcap_t *handle;

    // Find available network devices

    if (pcap_findalldevs(&alldevs, errbuf) == -1)
    {
        cerr << "Error finding devices: "
             << errbuf << endl;

        return 1;
    }

    if (alldevs == nullptr)
    {
        cout << "No device found." << endl;
        return 1;
    }

    // Select first available device

    pcap_if_t *device = alldevs;

    cout << "Using device: "
         << device->name << endl;


    // Open the network device

    handle = pcap_open_live(
        device->name,
        BUFSIZ,
        1,
        1000,
        errbuf
    );

    if (handle == nullptr)
    {
        cerr << "Could not open device: "
             << errbuf << endl;

        pcap_freealldevs(alldevs);

        return 1;
    }


    // Check link-layer type

    if (pcap_datalink(handle) != DLT_EN10MB)
    {
        cerr << "This program expects Ethernet packets."
             << endl;

        pcap_close(handle);
        pcap_freealldevs(alldevs);

        return 1;
    }


    cout << "Starting packet capture..." << endl;


    // Capture 10 packets

    pcap_loop(handle, 10, packetHandler, nullptr);


    // Close capture session

    pcap_close(handle);

    // Free device information

    pcap_freealldevs(alldevs);

    return 0;
}
