package util;

    import org.hibernate.Session;
    import org.hibernate.SessionFactory;
    import org.hibernate.boot.registry.StandardServiceRegistry;
    import org.hibernate.boot.registry.StandardServiceRegistryBuilder;
    import org.hibernate.cfg.Configuration;

    public class hibernateUtil {
	    private static SessionFactory sessionFactory;
	    private static Session session;
	
	    static
	    {
		    //创建Configuration对象,读取主配置文件cfg.xml,完成初始化
		    Configuration config = new Configuration().configure();
		    //hibernate 4.x 使用的方法,获取会话工厂
		    StandardServiceRegistryBuilder ssrb = new StandardServiceRegistryBuilder().applySettings(config.getProperties());
		    StandardServiceRegistry ssr = ssrb.build();
		    sessionFactory= config.buildSessionFactory(ssr);
		
	    }
	    //获取sessionFactory
	    public static SessionFactory getSessionFactory()
	    {
		    return sessionFactory;
	    }
	
	    //获取Session
	    public static Session getSession()
	    {
		    return sessionFactory.openSession();
	    }
	
    //关闭session
	    public static void closeSession(Session session)
	    {
		    if(session!=null)
		    {
			    session.close();
		    }
	    }
	
    }
