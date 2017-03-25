package juedaiyuer.test;

import java.util.List;

import org.apache.ibatis.session.SqlSession;
import org.junit.Test;

import juedaiyuer.entity.User;
import juedaiyuer.mapping.UserMapperI;
import juedaiyuer.util.MyBatisUtil;

/**
 * @author juedaiyuer
 * 
 *         1. Mybatis基于注解实现CURD单元测试
 * 
 */

public class TestCURDAnnotationMapper {

	@Test
	public void testAdd() {
		SqlSession sqlSession = MyBatisUtil.getSqlSession(true);
		
		// 得到UserMapperI接口的实现类对象，UserMapperI接口的实现类对象由动态创建出来
		UserMapperI mapper = sqlSession.getMapper(UserMapperI.class);

		User user = new User();
//		user.setName("厉倾城");
//		user.setAge(21);

		user.setName("苏子");
		user.setAge(20);
		
		int add = mapper.add(user);

		sqlSession.close();
		System.out.println(add);
	}
	
	@Test
	public void testUpdate(){
		SqlSession sqlSession = MyBatisUtil.getSqlSession(true);
		UserMapperI mapper = sqlSession.getMapper(UserMapperI.class);
		
		User user = new User();
		user.setId(5);
		user.setName("厉倾城");
		user.setAge(24);
		
		// 执行修改操作
		int retResult = mapper.update(user);
		sqlSession.close();
		System.out.println(retResult);
	}

	@Test
	public void testDelete() {
		SqlSession sqlSession = MyBatisUtil.getSqlSession(true);
		UserMapperI mapper = sqlSession.getMapper(UserMapperI.class);

		int retResult = mapper.deleteById(6);

		sqlSession.close();
		System.out.println(retResult);
	}
	
	@Test
	public void testGetUser(){
		SqlSession sqlSession = MyBatisUtil.getSqlSession(true);
		UserMapperI mapper = sqlSession.getMapper(UserMapperI.class);
		
		User user = mapper.getById(3);
		sqlSession.close();
		System.out.println(user);
		
	}

	@Test
	public void testGetAll() {
		SqlSession sqlSession = MyBatisUtil.getSqlSession(true);
		UserMapperI mapper = sqlSession.getMapper(UserMapperI.class);

		List<User> userList = mapper.getAll();

		sqlSession.close();
		System.out.println(userList);
	}

}