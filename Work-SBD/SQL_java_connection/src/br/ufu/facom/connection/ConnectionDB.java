package br.ufu.facom.connection;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;

public class ConnectionDB {
	
	private static final String USER = "postgres";
	private static final String PASSWORD = "postgres";
	private static final String SCHEMA = "trabalho";
	
	/////////////////////////////// Interface banco de dados ///////////////////////////////
	public static Connection getConnection() {
		Connection c = null;
		try {
			Class.forName("org.postgresql.Driver");
			String url = "jdbc:postgresql://localhost:5432/Trabalho?currentSchema=" + SCHEMA;
			c = DriverManager.getConnection(url, USER, PASSWORD);
		} catch (ClassNotFoundException ex) {
			ex.printStackTrace();
		} catch (SQLException ex) {
			ex.printStackTrace();
		}
		return c;
	}
	
	public static void executeSQL(String sql) {
		Connection c = getConnection();
		if(c != null) {
			Statement s;
			try {
				s = c.createStatement();
				s.executeUpdate(sql);
				c.close();
			} catch (SQLException e) {
				e.printStackTrace();
			}
		}
	}
	
	/////////////////////////////// Shoppings ///////////////////////////////	
	public static boolean isShoppingCadastrado(String nome) {
		Connection c = getConnection();
		if(c != null) {
			Statement s;
			try {
				s = c.createStatement();
				ResultSet rs = s.executeQuery("select nome from shopping where nome = '" + nome + "'");
				String n = "";
				while(rs.next()) {
					n = rs.getString(1);
				}
				c.close();
				
				if(n.isEmpty())
					return false;
				
			} catch (SQLException ex) {
				ex.printStackTrace();
			}
		}
		return true;
	}
	
	public static ArrayList<String> getShoppings() {
		ArrayList<String> shoppings = new ArrayList<String>();
		Connection c = getConnection();
		if(c != null) {
			Statement s;
			try {
				s = c.createStatement();
				ResultSet rs = s.executeQuery("select nome from shopping");
				while(rs.next()) {
					String temp = rs.getString(1);
					shoppings.add(temp);
				}
				c.close();
			} catch (SQLException ex) {
				ex.printStackTrace();
			}
		}
		return shoppings;
	}

	public static String getShoppingEnd(String nome) {
		Connection c = getConnection();
		String endereco = "";
		if(c != null) {
			Statement s;
			try {
				s = c.createStatement();
				ResultSet rs = s.executeQuery("select endereco from shopping where nome = '" + nome + "'");
				while(rs.next()) {
					endereco = rs.getString(1);
				}
				c.close();
			} catch (SQLException ex) {
				ex.printStackTrace();
			}
			
		}
		return endereco;
	}
	
	public static String getShoppingTelefone(String nome) {
		Connection c = getConnection();
		String telefone = "";
		if(c != null) {
			Statement s;
			try {
				s = c.createStatement();
				ResultSet rs = s.executeQuery("select telefone from shopping where nome = '" + nome + "'");
				while(rs.next()) {
					telefone= rs.getString(1);
				}
			} catch (SQLException ex) {
				ex.printStackTrace();
			}
			
		}
		return telefone;
	}
	
	/////////////////////////////// Pracas ///////////////////////////////
	public static void insertPraca(String nome_shopping, String id, String area, String n_cad, String n_mesa) throws SQLException{
		Connection c = getConnection();
		if(c != null) {
			Statement s;
			try {
				s = c.createStatement();
				s.executeUpdate("insert into praca_alimentacao values (" + id + ", '" + nome_shopping + "')");				
				s.executeUpdate("insert into espaco_praca values (" + id + ", " + area + ", " + n_cad + ", " + n_mesa + ")");
			}catch(SQLException ex) {
				s = c.createStatement();
				s.executeUpdate("delete from praca_alimentacao where id = " + id);
				throw ex;
			} finally {
				c.close();
			}
		}
	}
	
	public static void updatePraca(String id, String area, String n_cad, String n_mesa) {
		Connection c = getConnection();
		if(c != null) {
			Statement s;
			try {
				s = c.createStatement();
				s.executeUpdate("update espaco_praca set metros_quadrados = " + area + ", n_cad = " + n_cad + ", n_mesa = " + n_mesa + " where id_praca = " + id);
				c.close();
			} catch (SQLException ex) {
				ex.printStackTrace();
			}
		}
	}
	
	public static boolean isPracaCadastrada(String id) {
		Connection c = getConnection();
		String temp = "";
		if(c != null) {
			Statement s;
			try {
				s = c.createStatement();
				ResultSet rs = s.executeQuery("");
				while(rs.next()) {
					temp = rs.getString(1);
				}
				if(!temp.isEmpty()) {
					return true;
				}
				c.close();
			} catch (SQLException e) {
				e.printStackTrace();
			}
		}
		return false;
	}
	
	public static ArrayList<String> getPracas(String shopping) {
		ArrayList<String> pracas = new ArrayList<String>();
		Connection c = getConnection();
		if(c != null) {
			Statement s;
			try {
				s = c.createStatement();
				ResultSet rs = s.executeQuery(
						  "select espaco_praca.id_praca "
						+ "from espaco_praca join praca_alimentacao on espaco_praca.id_praca = praca_alimentacao.id "
						+ "where praca_alimentacao.nome_shop = '" + shopping + "'");
				while(rs.next()) {
					pracas.add(rs.getString(1));
				}
				c.close();
			} catch (SQLException ex) {
				ex.printStackTrace();
			}
			
		}
		return pracas;
	}
	
	public static String getAreaPraca(String id) {
		Connection c = getConnection();
		String area = "";
		if(c != null) {
			Statement s;
			try {
				s = c.createStatement();
				ResultSet rs = s.executeQuery(
						"select espaco_praca.metros_quadrados"
						+ " from espaco_praca, praca_alimentacao, shopping"
						+ " where espaco_praca.id_praca = praca_alimentacao.id and praca_alimentacao.nome_shop = shopping.nome and espaco_praca.id_praca = " + id);
				while(rs.next()) {
					area = rs.getString(1);
				}
				c.close();
			} catch (SQLException ex) {
				ex.printStackTrace();
			}
			
		}
		return area;
	}

	public static String getNumCadeirasPraca(String id) {
		Connection c = getConnection();
		String n = "";
		if(c != null) {
			Statement s;
			try {
				s = c.createStatement();
				ResultSet rs = s.executeQuery(
						"select espaco_praca.n_cad"
						+ " from espaco_praca, praca_alimentacao, shopping"
						+ " where espaco_praca.id_praca = praca_alimentacao.id and praca_alimentacao.nome_shop = shopping.nome and espaco_praca.id_praca = " + id);
				while(rs.next()) {
					n = rs.getString(1);
				}
				c.close();
			} catch (SQLException ex) {
				ex.printStackTrace();
			}
			
		}
		return n;
	}
	
	public static String getNumMesasPraca(String id) {
		Connection c = getConnection();
		String n = "";
		if(c != null) {
			Statement s;
			try {
				s = c.createStatement();
				ResultSet rs = s.executeQuery(
						"select espaco_praca.n_mesa"
						+ " from espaco_praca, praca_alimentacao, shopping"
						+ " where espaco_praca.id_praca = praca_alimentacao.id and praca_alimentacao.nome_shop = shopping.nome and espaco_praca.id_praca = " + id);
				while(rs.next()) {
					n = rs.getString(1);
				}
				c.close();
			} catch (SQLException ex) {
				ex.printStackTrace();
			}
			
		}
		return n;
	}
	
	/////////////////////////////// Utils ///////////////////////////////
	@SuppressWarnings("resource")
	public static int getProximoIdLivre() {
		Connection c = getConnection();
		int id = 0;
		if(c != null) {
			Statement s;
			try {
				s = c.createStatement();
				ResultSet rs;
				rs = s.executeQuery("select id from praca_alimentacao where id = " + id);
				while(rs.next()) {
					if(rs.getString(1).isEmpty())
						return id;
					rs = s.executeQuery("select id from praca_alimentacao where id = " + ++id);
				}
				c.close();
			} catch (SQLException ex) {
				ex.printStackTrace();
			}
		}
		return id;
	}
}
