package br.ufu.facom.gui;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.SQLException;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JTextField;

import br.ufu.facom.connection.ConnectionDB;
import br.ufu.facom.utils.Item;

public class AddPraca {
	private JComboBox<Item> cb;
	private boolean atualizar;
	private SQLJava sql;
	
	private final JFrame frame = new JFrame();
	private final JLabel lblArea = new JLabel("Área:");
	private final JTextField txtArea = new JTextField();
	private final JTextField txtCadeiras = new JTextField();
	private final JLabel lblCadeira = new JLabel("Qtd cadeiras:");
	private final JLabel lblQtdMesas = new JLabel("Qtd mesas:");
	private final JTextField txtMesas = new JTextField();
	private final JButton btnCancelar = new JButton("Cancelar");
	private final JButton btnConfirmar = new JButton("Confirmar");
	
	public AddPraca(JComboBox<Item> cb, String shopping, SQLJava sql) {
		this.cb = cb;
		this.atualizar = false;
		this.sql = sql;
		
		startFrame(shopping);
	}
	
	public AddPraca(JComboBox<Item> cb, String shopping, String area, String ncad, String nmesa, SQLJava sql) {
		this.cb = cb;
		this.atualizar = true;
		this.sql = sql;
		
		txtArea.setText(ConnectionDB.getAreaPraca(((Item)cb.getSelectedItem()).getId()));
		txtCadeiras.setText(ConnectionDB.getNumCadeirasPraca(((Item)cb.getSelectedItem()).getId()));
		txtMesas.setText(ConnectionDB.getNumMesasPraca(((Item)cb.getSelectedItem()).getId()));
		
		startFrame(shopping);
	}
	
	private void startFrame(String shopping) {
		txtArea.setColumns(10);
		txtCadeiras.setColumns(10);
		txtMesas.setColumns(10);
		txtArea.setBounds(110, 10, 118, 19);
		txtCadeiras.setBounds(110, 30, 118, 19);
		txtMesas.setBounds(110, 50, 118, 19);
		lblArea.setBounds(10, 10, 47, 15);
		lblCadeira.setBounds(10, 30, 100, 15);
		lblQtdMesas.setBounds(10, 50, 100, 15);
		btnCancelar.setBounds(10, 80, 105, 25);
		btnConfirmar.setBounds(120, 80, 105, 25);
		
		txtArea.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				addEvent(shopping);
			}
		});
		
		txtCadeiras.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				addEvent(shopping);
			}
		});
		
		txtMesas.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				addEvent(shopping);
			}
		});
		
		btnConfirmar.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				addEvent(shopping);
			}
		});
		
		btnCancelar.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				frame.dispose();
			}
		});
		
		frame.getContentPane().setLayout(null);
		frame.getContentPane().add(lblArea);
		frame.getContentPane().add(txtArea);
		frame.getContentPane().add(txtCadeiras);
		frame.getContentPane().add(lblCadeira);
		frame.getContentPane().add(lblQtdMesas);
		frame.getContentPane().add(txtMesas);
		frame.getContentPane().add(btnCancelar);
		frame.getContentPane().add(btnConfirmar);

		frame.setVisible(true);
		frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		frame.setResizable(false);
		frame.setSize(240, 145);
		frame.setLocationRelativeTo(null);
		if(atualizar)
			frame.setTitle("Atualizar praça");
		else
			frame.setTitle("Adicionar praça");
	}
	
	private void addEvent(String shopping) {
		// Inserir praca
		if(!atualizar) {
			int id = ConnectionDB.getProximoIdLivre();
			try {
				ConnectionDB.insertPraca(shopping, String.valueOf(id), txtArea.getText(), txtCadeiras.getText(), txtMesas.getText());
				if(cb.getItemCount() <= 0) {
					cb.setEnabled(true);
				}
				cb.addItem(new Item(cb.getItemCount() + 1, String.valueOf(id)));
				cb.setSelectedIndex(cb.getItemCount()-1);
				frame.dispose();
				sql.loadInfos();
			} catch (SQLException ex) {
				JOptionPane.showMessageDialog(null, "Por favor, preencha todos os campos com números", "ERRO", JOptionPane.ERROR_MESSAGE);
			}
		} else {
			if(cb.getItemCount() <= 0) {
				JOptionPane.showMessageDialog(null, "É necessário que ao menos uma praça de alimentação esteja cadastrada", "ERRO", JOptionPane.ERROR_MESSAGE);
			} else {
				ConnectionDB.updatePraca(((Item)cb.getSelectedItem()).getId(), txtArea.getText(), txtCadeiras.getText(), txtMesas.getText());
			}				
			frame.dispose();
			sql.loadInfos();
		}
	}
}
