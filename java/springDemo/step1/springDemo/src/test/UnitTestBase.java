package test;

import org.junit.After;
import org.junit.Before;
import org.springframework.beans.BeansException;
import org.springframework.context.support.ClassPathXmlApplicationContext;
import org.springframework.util.StringUtils;

import juedaiyuer.OneInterface;

public class UnitTestBase {

	private ClassPathXmlApplicationContext context;

	private String springXmlpath;

	public UnitTestBase() {
	}

	public UnitTestBase(String springXmlpath) {
		this.springXmlpath = springXmlpath;
	}

	@Before
	public void before() {
		if (StringUtils.isEmpty(springXmlpath)) {
			springXmlpath = "classpath*:spring-*.xml";
		}
		try {
			context = new ClassPathXmlApplicationContext(springXmlpath.split("[,\\s]+"));
			context.start();
			System.out.println("单元测试基类---Before");
		} catch (BeansException e) {
			e.printStackTrace();
		}

	}

	@After
	public void after() {
		context.destroy();
		System.out.println("单元测试基类---After");
	}

	@SuppressWarnings("unchecked")
	protected <T extends Object> T getBean(String beanId) {
		try {
			System.out.println("单元测试基类---通过id获取实例");
			return (T) context.getBean(beanId);

		} catch (BeansException e) {
			e.printStackTrace();
			return null;
		}
	}

	protected <T extends Object> T getBean(Class<T> clazz) {
		try {
			System.out.println("单元测试基类---通过clazz获取实例");
			return (T) context.getBean(clazz);
		} catch (BeansException e) {
			e.printStackTrace();
			return null;
		}
	}

}
