	package juedaiyuer.util;

	import java.io.InputStream;

	import org.apache.ibatis.session.SqlSession;
	import org.apache.ibatis.session.SqlSessionFactory;
	import org.apache.ibatis.session.SqlSessionFactoryBuilder;

	public class MyBatisUtil {
	
		//获取SqlSessionFactory
		public static SqlSessionFactory getSqlSessionFactory()
		{
			// 项目配置文件所在位置
			String resource = "conf.xml";
			InputStream is = MyBatisUtil.class.getClassLoader().getResourceAsStream(resource);
			SqlSessionFactory factory = new SqlSessionFactoryBuilder().build(is);
			return factory;
		}
	
		//获取SqlSession
		public static SqlSession getSqlSession()
		{
			return getSqlSessionFactory().openSession();
		}
	
		//选择是否自动提交
		public static SqlSession getSqlSession(boolean isAutoCommit)
		{
			return getSqlSessionFactory().openSession(isAutoCommit);
		}
	
	}