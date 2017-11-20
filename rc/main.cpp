#include <bits/stdc++.h>
#include <ns3/core-module.h>
#include <ns3/point-to-point-module.h>
#include <ns3/internet-module.h>
#include <ns3/applications-module.h>
#include "ns3/olsr-helper.h"
#include <ns3/netanim-module.h>
#include <ns3/bs-net-device.h>
#include <ns3/csma-module.h>
#include <ns3/uan-module.h>

using namespace std;
using namespace ns3;

int main () {
	//LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_ALL);
	//LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_ALL);
	//LogComponentEnable("LiIonEnergySource", LOG_LEVEL_DEBUG);
	//LogComponentEnableAll(LOG_LEVEL_DEBUG);

	std::string outputFolder = "output/";
	NodeContainer nodes, nodesRede1, nodesRede2, nodesRede3;
	nodes.Create(4);
	nodesRede1.Add(nodes.Get(0));
	nodesRede1.Add(nodes.Get(1));
	nodesRede2.Add(nodes.Get(1));
	nodesRede2.Add(nodes.Get(2));
	nodesRede3.Add(nodes.Get(2));
	nodesRede3.Add(nodes.Get(3));

	Ipv4StaticRoutingHelper staticRouting;
	OlsrHelper olsrRouting;

	Ipv4ListRoutingHelper routeHelper;
	routeHelper.Add(staticRouting, 0);
	routeHelper.Add(olsrRouting, 10);

	InternetStackHelper internetHelper;
	internetHelper.SetRoutingHelper(routeHelper);
	internetHelper.Install(nodes);
	internetHelper.EnablePcapIpv4All(outputFolder+"pcap");

	NetDeviceContainer netInterfaces, netInterfacesRede1, netInterfacesRede2, netInterfacesRede3;
	PointToPointHelper pointHelper;
	pointHelper.SetChannelAttribute("Delay",StringValue("5ms"));
	netInterfacesRede1 = pointHelper.Install(nodesRede1.Get(1),nodesRede1.Get(0));
	netInterfacesRede2 = pointHelper.Install(nodesRede2.Get(0),nodesRede2.Get(1));
	netInterfacesRede3 = pointHelper.Install(nodesRede3.Get(0),nodesRede3.Get(1));

	pointHelper.EnablePcapAll(outputFolder+"pcap", true);

	Ipv4InterfaceContainer interfaceRede1, interfaceRede2, interfaceRede3;
	Ipv4AddressHelper ipv4Helper;
	ipv4Helper.SetBase("192.168.1.0","255.255.255.0");
	interfaceRede1 = ipv4Helper.Assign(netInterfacesRede1);
	ipv4Helper.NewNetwork();

	ipv4Helper.SetBase("192.168.2.0","255.255.255.0");
	interfaceRede2 = ipv4Helper.Assign(netInterfacesRede2);
	ipv4Helper.NewNetwork();

	ipv4Helper.SetBase("192.168.3.0","255.255.255.0");
	interfaceRede3 = ipv4Helper.Assign(netInterfacesRede3);
	ipv4Helper.NewNetwork();

	//Configurar aplicações
	ApplicationContainer clientApp, serverApp;

	UdpEchoServerHelper echoServerHelper(8080);
	serverApp = echoServerHelper.Install(nodesRede1.Get(0)); //Instala servidor echo em 192.168.1.0 ou 1

	UdpEchoClientHelper echoClientHelper(nodesRede1.Get(0)->GetObject<Ipv4>()->GetAddress(1,0).GetLocal(),8080);
	clientApp = echoClientHelper.Install(nodesRede3.Get(1)); //Instala cliente echo em 192.168.1.1 ou 2

	serverApp.Start(Seconds(1));
	serverApp.Stop(Seconds(20));
	clientApp.Start(Seconds(2));
	clientApp.Stop(Seconds(19));

// ---- A partir daqui, tem um servidor escutando na porta 8080 e um cliente mandando mensagens para ela

	//Exportar simulação para netanim
	BaseStationNetDevice b;
	SubscriberStationNetDevice s;
	CsmaNetDevice c;
	UanNetDevice u;

	AnimationInterface anim(outputFolder+"anim2.xml");
	anim.SetMaxPktsPerTraceFile(0xFFFFFFFF);
	anim.EnablePacketMetadata(true);
	anim.EnableIpv4RouteTracking (outputFolder+"routingtable-wireless.xml", Seconds (0), Seconds (9), Seconds (0.25));

	//Executar simulação por 10 segundos e depois destruir
	Simulator::Stop(Seconds(20));
	Simulator::Run();
	Simulator::Destroy();
}