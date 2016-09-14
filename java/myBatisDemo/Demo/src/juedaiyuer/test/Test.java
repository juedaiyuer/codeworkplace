	package juedaiyuer.test;

	import java.io.InputStream;
	import java.sql.Connection;

	import org.apache.ibatis.session.Configuration;
	import org.apache.ibatis.session.ExecutorType;
	import org.apache.ibatis.session.SqlSession;
	import org.apache.ibatis.session.SqlSessionFactory;
	import org.apache.ibatis.session.SqlSessionFactoryBuilder;
	import org.apache.ibatis.session.TransactionIsolationLevel;

	import juedaiyuer.entity.User;

	public class Test {
		public static void main(String[] args) {
			//mybatis的配置文件
		
			String resource = "conf.xml";
		
			//使用类加载器加载mybatis的配置文件及其相关联的映射
		
			InputStream is = Test.class.getClassLoader().getResourceAsStream(resource);
		
			//构建sqlSession的工厂
		
			SqlSessionFactory sessionFactory = new SqlSessionFactoryBuilder().build(is);
		
			SqlSession session = sessionFactory.openSession();
			String statement = "juedaiyuer.mapping.userMapper.getUser";
			User user = (User) session.selectOne(statement, 3);
			System.out.println(user);

			session.close();
		}

	}