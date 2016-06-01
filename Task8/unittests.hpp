namespace
{
	bool fail = false;
}

template <typename T>
void testEqual(T expected, T actual, const std::string& failmessage)
{
	if(!(expected == actual)){
		std::cerr << failmessage.c_str() << std::endl;
		fail = true;
	}
}

bool testTargets(){

}

bool testPlanets(){

}

bool testSpaceships(){

}

void testAll(){
    
}
