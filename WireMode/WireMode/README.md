This is an unstructured version of the specification for the P2P network.

Nodes find the network through a relay server which gives them the address of a few nodes in the network they can connect through.

# Structure and connecting

Notes: All cluster control nodes knowing exactly where all other nodes are seems like a bottleneck for scaling. Each cluster node should have a shortlist of local nodes. I'll have to 
figure out what local means later and how to ensure clusters don't get lost.


Nodes are seperated into clusters of nodes. Each cluster has a designated cluster controller which is able to communicate with other clusters. It also has a backup cluster controller.

Nodes in clusters know all other nodes in the cluster.

All cluster controller nodes are linked to the relay server. The cluster controller knows how many nodes are in the cluster. It also knows the maximum nodes allowed in a cluster.

A new node wants to join the network, it communicates with the relay server. The relay server in turn sends join requests to all the cluster controllers and the controllers check if the cluster has room for another node. If it does it'll send a message back to the relay server with the ip address of a node on the cluster that isn't the controller. The ip address sent from the relay server of the new node that might be joining is distributed amongst the nodes in the cluster from the controller and is stored temporarily.

If the relay recieves multiple OK messages from the clusters it sent requests to, it picks one randomly and signals the node to send a connection request to one of the ip addresses sent back from the cluster controller (multiple node ip addresses are sent because a node might disconnect during the process. If this occurred, it can switch to a different node).

The new node's connection request to the cluster node is received. If the new node's ip address matches the one it has stored then it'll authorise the request and the node will send out a message to all other nodes in the cluster informing them of the connection success. They will all then add the temporary ip address from before to their list of contacts in the cluster. (Using the ip address from before instead of requesting an ip from the new node will prevent people spoofing their ip address when gaining access to the network).

The new node will then be sent an entire copy of the cluster's list of nodes as a return message from its connection request.

(Note: the cluster that recieves the new node should send a network wide message stating a new node has joined which will cause nodes that stored the temporary ip address to delete the data. If the relay sent this message instead of the nodes then someone could hack the relay server, make lots of join requests and program the relay to not send the message causing ip addresses to pile up in the nodes and cause drain memory in the nodes resulting in a denial of service attack occuring.)

# Sending messages
A node wants to send a message to another node. It doesn't have to do it through the network. The network is largely there for discovery. A mechanism for ensuring that nodes can find each other. The network is also there to authorise the connection between nodes so that the nodes are certain they are talking to who they think they're talking to.

End to end encryption will be available.

Nodes could have private keys which could be used to sign their requests. People have the public keys of their friends and use that to authenticate whether they're who they say they are?

If I know the person I want to send the message to, I transmit a network wide request using some data that's encrypted with my private key.

Only the sender has their public key so if I can decrypt the message with their public key I know the request is from them.

Nodes need a way of identifying each other. A way to do this could be through usernames combined with Guids?

Assume each node has an identifier.

Node A wants to send a message to Node B.

Node A sends a network wide communication request with the intended recipient being Node B. Once node B recieves the request with Node B's identifier in it, it will examine the request.

The request will contain the sender's unique identifier and some text encrypted with the sender's private key. If Node A is on Node B's friend list it will already have Node A's public key. If not then it will send a request to get Node A's public key (this is where we need to worry about security). It will use Node A's public key to verify if the request was sent by Node A. If the verification is successful then Node B will send a network wide message addressed to node A with a text message encrypted with Node B's private key. Node A will verify that the response came from Node B again.

Node B's response will contain an ip address encrypted with Node A's public key.

Perhaps a simpler, more secure protocol for setting up comm channels could be made.

Node A sends a message to Node B with Node A's ip address encrypted with Node B's public key. Upon recieving the message it sends a message directly to Node A using its ip address that contains text encrypted with Node B's private key. Node A recieves the direct message and uses Node B's public key to verify that the message came from them. If it does then then both parties have verified that they are who they say they are.

Security measures: Ensure that no messages can be recieved on the port that's opened on Node B to Node A until verification is complete. Otherwise a random node could send a request to another node causing them to open a port on their pc which could be used to hack them.

(if you encrypt a message with the person's public key, only they can open it because they need their private key)

(The node's should have a static guid identifier they store locally.)

There needs to be a state based system in place so that A will only accept a connection from another node directly once it's send out a comm request. Problem: What is someone on the same cluster knows a's ip address and waits until they send out a request before connecting to them pretending to be the person they send out a request to. Granted, they couldn't finish the communication handshake because they don't know B's private key but they would have a direct open channel to A through which they could try and hack into A. We should send a port number to B as well as an ip. On top of that we should give B a password they need to transmit to verify that they recieved the message. If a wrong password is sent even once the connection is terminated. The password will change each time a connection request is made so bruteforcing it by constantly trying to connect would be impossible.

The connection request should contain:

Sender Identifier. Sender IP Address. Sender Port. Sender Password.

(What would happen if we sent A's public key?)

(secure transmission of public keys should use a voting system. B requests A's public key by sending a request to the network. Multiple nodes reply and the correct key is determined by how many nodes give that key as a response. This would prevent malicious nodes from sending false public keys but it also wouldn't work with the cluster system because it means the cluster controller would be a single point of attack as it's transmitting to other clusters and it could be compromised.)

We send a request network wide to identify Node B and get it's ip address. We then distribute that IP across all nodes in the cluster. All the nodes that receive the new ip must send verification messages to all other nodes in the cluster to ensure that they all have the same IP and the controller isn't decieving them with different IPs to influence the vote.

All nodes in the cluster request seperately the public key from Node A. They then all transmit the public key to the ip address they have. Node B will recieve all the requests and then adds up how many of the public keys sent are the same. The version of the public key with the most sent will be considered the correct public key. This voting system is to stop single nodes from being compromised and sending the wrong public key. A majority of nodes in a cluster will need to be compromised for this system to be hacked.

This public key sharing system will be used when two nodes want to make friends. They will store the verified public keys for future use so this system doesn't need to be used again.

(a weakness could be in the part where the controller sends the ip to all the nodes in the cluster)

(A single malicious controller could give a false ip address to the nodes. It could then use a server to send votes to the ip address with a different public key)

(A way around this could be to require votes to be verified. Before a vote is cast, it must prove it is who it says it is by maybe sending an ip address with it that it can send a message back to.)

(ensure that the node recieving the votes checks that the ip addresses are different. A better verification system to ensure votes are valid would be good)

When the backup control node becomes the control node it should broadcast a message notifying all nodes. If the controller becomes unreachable then the backup takes over.

(We should have multiple types of messages, single broadcasts and handshake types. Handshakes should have multithreaded and non threaded to indicate whether the response is needed immediately.

(Note: this new controller broadcast could be a security weakeness. If a random node declares itself the controller it will be an issue. Maybe when recieving this message it will check if the backup sent it?)

Types of message:

New controller notification (Broadcast)
Notifies other nodes of a new cluster controller. Handshake:
Node A sends a request to Node B with the message type and the details of Node A (sender)

Node B sends a message back informing Node A that the request was received and accepted. The handshake is complete.

Join cluster request (directed)

A direct request from a new node to join the cluster. The joiner will give their node identifier and their public key Handshake:
Node A sends a message to the relay server with the message type and the details of Node A.

New node IP update (Broadcast)

A notification that a new node with the given IP will be joining the cluster and to only accept join requests from that IP address.
Cluster availability request (directed)
A request from the relay server to check if the cluster has space for a new node and if so, return a few IP addresses of nodes that can be used to connect to the cluster (not the controller).
Cluster directory notification (directed)
Gives the directed node the entire list of IP addresses for nodes in the cluster
Node join status notification (broadcast)
Informs all other nodes in the cluster whether the new node joined successfully.