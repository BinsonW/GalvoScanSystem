//
// SocketReactorTest.cpp
//
// $Id: //poco/1.4/Net/testsuite/src/SocketReactorTest.cpp#1 $
//
// Copyright (c) 2005-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


// 
// 
// SocketReactorTest::SocketReactorTest(const std::string& name): CppUnit::TestCase(name)
// {
// }
// 
// 
// SocketReactorTest::~SocketReactorTest()
// {
// }
// 
// 
// void SocketReactorTest::testSocketReactor()
// {
// 	SocketAddress ssa;
// 	ServerSocket ss(ssa);
// 	SocketReactor reactor;
// 	SocketAcceptor<EchoServiceHandler> acceptor(ss, reactor);
// 	SocketAddress sa("localhost", ss.address().port());
// 	SocketConnector<ClientServiceHandler> connector(sa, reactor);
// 	ClientServiceHandler::setOnce(true);
// 	ClientServiceHandler::resetData();
// 	reactor.run();
// 	std::string data(ClientServiceHandler::data());
// 	assert (data.size() == 1024);
// 	assert (!ClientServiceHandler::readableError());
// 	assert (!ClientServiceHandler::writableError());
// 	assert (!ClientServiceHandler::timeoutError());
// }
// 
// 
// void SocketReactorTest::testSetSocketReactor()
// {
// 	SocketAddress ssa;
// 	ServerSocket ss(ssa);
// 	SocketReactor reactor;
// 	SocketAcceptor<EchoServiceHandler> acceptor(ss);
// 	acceptor.setReactor(reactor);
// 	SocketAddress sa("localhost", ss.address().port());
// 	SocketConnector<ClientServiceHandler> connector(sa, reactor);
// 	ClientServiceHandler::setOnce(true);
// 	ClientServiceHandler::resetData();
// 	reactor.run();
// 	std::string data(ClientServiceHandler::data());
// 	assert(data.size() == 1024);
// 	assert(!ClientServiceHandler::readableError());
// 	assert(!ClientServiceHandler::writableError());
// 	assert(!ClientServiceHandler::timeoutError());
// }
// 
// 
// void SocketReactorTest::testParallelSocketReactor()
// {
// 	SocketAddress ssa;
// 	ServerSocket ss(ssa);
// 	SocketReactor reactor;
// 	ParallelSocketAcceptor<EchoServiceHandler, SocketReactor> acceptor(ss, reactor);
// 	SocketAddress sa("localhost", ss.address().port());
// 	SocketConnector<ClientServiceHandler> connector1(sa, reactor);
// 	SocketConnector<ClientServiceHandler> connector2(sa, reactor);
// 	SocketConnector<ClientServiceHandler> connector3(sa, reactor);
// 	SocketConnector<ClientServiceHandler> connector4(sa, reactor);
// 	ClientServiceHandler::setOnce(false);
// 	ClientServiceHandler::resetData();
// 	reactor.run();
// 	std::string data(ClientServiceHandler::data());
// 	assert (data.size() == 4096);
// 	assert (!ClientServiceHandler::readableError());
// 	assert (!ClientServiceHandler::writableError());
// 	assert (!ClientServiceHandler::timeoutError());
// }
// 
// 
// void SocketReactorTest::testSocketConnectorFail()
// {
// 	SocketReactor reactor;
// 	reactor.setTimeout(Poco::Timespan(3, 0));
// 	SocketAddress sa("192.168.168.192", 12345);
// 	FailConnector connector(sa, reactor);
// 	assert (!connector.failed());
// 	assert (!connector.shutdown());
// 	reactor.run();
// 	assert (connector.failed());
// 	assert (connector.shutdown());
// }
// 
// 
// void SocketReactorTest::testSocketConnectorTimeout()
// {
// 	ClientServiceHandler::setCloseOnTimeout(true);
// 	
// 	SocketAddress ssa;
// 	ServerSocket ss(ssa);
// 	SocketReactor reactor;
// 	SocketAddress sa("localhost", ss.address().port());
// 	SocketConnector<ClientServiceHandler> connector(sa, reactor);
// 	reactor.run();
// 	assert (ClientServiceHandler::timeout());
// }
// 
// 
// void SocketReactorTest::setUp()
// {
// 	ClientServiceHandler::setCloseOnTimeout(false);
// }
// 
// 
// void SocketReactorTest::tearDown()
// {
// }
// 
// 
// CppUnit::Test* SocketReactorTest::suite()
// {
// 	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("SocketReactorTest");
// 
// 	CppUnit_addTest(pSuite, SocketReactorTest, testSocketReactor);
// 	CppUnit_addTest(pSuite, SocketReactorTest, testParallelSocketReactor);
// 	CppUnit_addTest(pSuite, SocketReactorTest, testSocketConnectorFail);
// 	CppUnit_addTest(pSuite, SocketReactorTest, testSocketConnectorTimeout);
// 
// 	return pSuite;
// }
