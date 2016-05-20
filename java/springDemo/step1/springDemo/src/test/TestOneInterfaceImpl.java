package test;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.BlockJUnit4ClassRunner;

import juedaiyuer.OneInterface;

@RunWith(BlockJUnit4ClassRunner.class)
public class TestOneInterfaceImpl  extends UnitTestBase{
	public TestOneInterfaceImpl()
	{
		super("classpath*:spring-ioc.xml");
	}
	
	@Test
	public void testSay()
	{
		OneInterface oneInterface = super.getBean("oneInterface");
		oneInterface.say("this is a test");
	}

}
