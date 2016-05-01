package hibernateDemo;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStream;
import java.sql.Blob;
import java.util.Date;

import org.hibernate.Hibernate;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;

import org.hibernate.cfg.Configuration;
import org.hibernate.service.Service;
import org.hibernate.service.ServiceRegistry;
import org.hibernate.service.ServiceRegistryBuilder;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;

//测试类
public class StudentsTest {
	
	private SessionFactory sessionFactory;
	private Session session;
	private Transaction transaction;
	
	@Before
	public void init()
	{
		//创建配置对象
		Configuration config = new Configuration().configure();
		//创建服务注册对象
		ServiceRegistry serviceRegistry = new ServiceRegistryBuilder().applySettings(config.getProperties()).buildServiceRegistry();
		//创建会话工厂
		sessionFactory = config.buildSessionFactory(serviceRegistry);
		//会话对象
		session = sessionFactory.openSession();
		//开启事务
		transaction = session.beginTransaction();
		
	}
	
	@After
	public void destroy()
	{
		transaction.commit(); //先提交事务
		session.close();//关闭会话
		sessionFactory.close();
		
	}
	
	@Test
	public void testSaveStudents()
	{
		//生成一个学生对象
		
		Students s = new Students(1,"张三丰","男",new Date(),"武当山");
		session.save(s);
					
	}
	
	@Test
	public void testWriteBlob() throws Exception
	{
		Students s = new Students(1,"张三丰","男",new Date(),"武当山");
		//获得照片文件
		File f = new File("/home/juedaiyuer"+File.separator+"woman.jpg");
		//获得输入流
		InputStream input = new FileInputStream(f);
		//创建一个Blob对象
		Blob image = Hibernate.getLobCreator(session).createBlob(input,input.available());
		//设置照片属性
		s.setPictrue(image);
		session.save(s);
		
	}
	
	@Test
	public void testReadBlob() throws Exception
	{
		Students s = (Students)session.get(Students.class, 1);
		Blob image = s.getPictrue();
		//获得输入流
		InputStream input = image.getBinaryStream();
		//创建输出流
		File f = new File("/home/juedaiyuer"+File.separator+"woman2.jpg");
		//获得输出流
		OutputStream output = new FileOutputStream(f);
		//创建缓冲区
		byte[] buff = new byte[input.available()];
		input.read(buff);
		output.write(buff);
		input.close();
		output.close();
		
		
	}
		
}
