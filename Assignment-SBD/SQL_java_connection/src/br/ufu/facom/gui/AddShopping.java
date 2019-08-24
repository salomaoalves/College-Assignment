package br.ufu.facom.gui;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;

import br.ufu.facom.connection.ConnectionDB;

public class AddShopping {
	private boolean atualizar;
	private String updateName = "";
	
	private final JButton btnContinuar = new JButton("Confirmar");
	private final JButton btnCancelar = new JButton("Cancelar");
	private final JComboBox<String> comboBox;
	private final JPanel panel_1 = new JPanel();
	private final JLabel lblNome = new JLabel("Nome:");
	private final JLabel lblEndereo = new JLabel("Endereço:");
	private final JLabel lblTelefone = new JLabel("Telefone:");
	private final JTextField txtNome = new JTextField();
	private final JTextField txtEndereco = new JTextField();
	private final JTextField txtTelefone = new JTextField();
	private final JFrame frame;
	
	public AddShopping(JComboBox<String> comboBox) {
		frame = new JFrame();
		this.comboBox = comboBox;
		atualizar = false;
		startFrame();
	}
	
	// Editar shopping
	public AddShopping(JComboBox<String> combobox, String nome, String endereco, String telefone) {
		frame = new JFrame();
		this.comboBox = combobox;
		atualizar = true;
		this.updateName = nome;
		
		startFrame();
		txtNome.setText(nome);
		txtEndereco.setText(endereco);
		txtTelefone.setText(telefone);
	}
	
	private void startFrame() {
		txtNome.setColumns(10);
		txtEndereco.setColumns(10);
		txtTelefone.setColumns(10);		
		if(!atualizar)
			frame.setTitle("Adicionar Shopping");
		else
			frame.setTitle("Atualizar Shopping");
		frame.setVisible(true);
		frame.setSize(320, 180);
		frame.setResizable(false);
		frame.setAutoRequestFocus(false);
		frame.getContentPane().setLayout(null);
		frame.setLocationRelativeTo(null);
		frame.getContentPane().add(panel_1);
		
		panel_1.setLayout(null);
		
		txtNome.setBounds(85, 10, 192, 19);
		txtEndereco.setBounds(85, 35, 192, 19);
		txtTelefone.setBounds(85, 60, 192, 19);
		panel_1.setBounds(12, 12, 296, 125);
		lblNome.setBounds(10, 10, 66, 15);
		lblEndereo.setBounds(10, 35, 77, 15);
		lblTelefone.setBounds(10, 60, 66, 15);
		btnCancelar.setBounds(12, 91, 114, 25);
		btnContinuar.setBounds(159, 91, 114, 25);
		
		txtNome.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
				addEvent();
			}
		});
		
		txtEndereco.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
				addEvent();
			}
		});
		
		txtTelefone.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
				addEvent();
			}
		});
		
		btnContinuar.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
				addEvent();
			}
		});
		
		btnCancelar.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
				frame.dispose();
			}
		});
		
		panel_1.add(lblNome);
		panel_1.add(txtNome);
		panel_1.add(lblEndereo);
		panel_1.add(txtEndereco);
		panel_1.add(lblTelefone);
		panel_1.add(txtTelefone);
		panel_1.add(btnCancelar);
		panel_1.add(btnContinuar);
	}
	
	private void addEvent() {
		if(txtNome.getText().isEmpty())
			JOptionPane.showMessageDialog(null, "O shopping deve ter um nome", "ERRO", JOptionPane.ERROR_MESSAGE);
		else {
			// Caso tentando inserir um shopping já existente
			if(ConnectionDB.isShoppingCadastrado(txtNome.getText()) && !atualizar){
				if(JOptionPane.showConfirmDialog(null, "O shopping já está cadastrado, deseja atualizar os dados existentes?", "Aviso", JOptionPane.OK_CANCEL_OPTION) == JOptionPane.OK_OPTION) {
					ConnectionDB.executeSQL("update shopping set nome = '" + txtNome.getText() + "', endereco = '" + txtEndereco.getText() + "', telefone = '" + txtTelefone.getText() + "' where nome = '" + txtNome.getText() + "'");
					frame.dispose();
				}
			} else if (atualizar) {
				if(!updateName.equals(txtNome.getText()) && ConnectionDB.isShoppingCadastrado(txtNome.getText())) {
					System.out.println("Update : " + updateName + ", outro: " + txtNome.getText());
					JOptionPane.showMessageDialog(null, "Não é possível alterar o nome do shopping para " + txtNome.getText() + " pois já possui um shopping cadastrado com esse nome", "ERRO", JOptionPane.ERROR_MESSAGE);
				} else {
					ConnectionDB.executeSQL("update shopping set nome = '" + txtNome.getText() + "', endereco = '" + txtEndereco.getText() + "', telefone = '" + txtTelefone.getText() + "' where nome = '" + updateName + "'");
					comboBox.removeItem(updateName);
					comboBox.addItem(txtNome.getText());
					comboBox.setSelectedItem(txtNome.getText());
					frame.dispose();
				}
			} else { // Caso esteja inserindo um shopping
				ConnectionDB.executeSQL("insert into shopping values ( '" + txtNome.getText() + "', '" + txtEndereco.getText() + "', '" + txtTelefone.getText() + "')");;
				comboBox.addItem(txtNome.getText());
				if(comboBox.isEnabled() == false)
					  comboBox.setEnabled(true);
				frame.dispose();
				comboBox.setSelectedIndex(comboBox.getItemCount() - 1);
			}
		}
	}
}
