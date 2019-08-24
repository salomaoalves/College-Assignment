package br.ufu.facom.gui;

import java.awt.Color;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.util.ArrayList;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.border.EtchedBorder;
import javax.swing.border.LineBorder;
import javax.swing.border.TitledBorder;

import br.ufu.facom.connection.ConnectionDB;
import br.ufu.facom.utils.Item;

public class SQLJava {
	private final JFrame frmControlePracas = new JFrame();
	private final JPanel panel = new JPanel();
	private final JPanel panelShoppings = new JPanel();
	private final JButton btnAddShopping = new JButton("+");
	private final JButton btnRmShopping = new JButton("-");
	private final JComboBox<String> comboBoxShop = new JComboBox<String>();
	private final JPanel panelPracas = new JPanel();
	private final JLabel lblId = new JLabel("ID:");
	private final JLabel lblAreaTitle = new JLabel("Área:");
	private final JLabel lblArea = new JLabel("Não definido");
	private final JLabel lblNumCadeirasTitle = new JLabel("Cadeiras:");
	private final JButton btnRestaurantes = new JButton("Restaurantes");
	private final JLabel lblNumCadeiras = new JLabel("Não definido");
	private final JLabel lblNumMesasTitle = new JLabel("Mesas:");
	private final JButton btnEditarShopping = new JButton("Editar");
	private final JButton btnAddId = new JButton("+");
	private final JButton btnRmId = new JButton("-");
	private final JButton btnEditarId = new JButton("Editar");
	private final JComboBox<Item> comboBoxId = new JComboBox<Item>();
	private final JPanel panelIdPraca = new JPanel();
	private final JPanel panelInfo = new JPanel();
	private final JLabel lblNumMesas = new JLabel("Não definido");
	
	public static void main (String[] args) {
		new SQLJava();
	}
	
	public SQLJava() {
		start();
	}
	
	public void start() {
		frmControlePracas.setIconImage(Toolkit.getDefaultToolkit().getImage(SQLJava.class.getResource("/br/ufu/facom/images/ufu_logo.png")));
		frmControlePracas.setResizable(false);
		frmControlePracas.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frmControlePracas.getContentPane().setLayout(null);
		frmControlePracas.setVisible(true);
		frmControlePracas.setSize(800,600);
		frmControlePracas.setTitle("Controle de praças de alimentação");
		frmControlePracas.setLocationRelativeTo(null);
		frmControlePracas.getContentPane().add(panel);
		
		panel.setLayout(null);
		panelShoppings.setLayout(null);
		
		panelShoppings.setBorder(new TitledBorder(new LineBorder(new Color(184, 207, 229)), "Shopping", TitledBorder.LEADING, TitledBorder.TOP, null, new Color(51, 51, 51)));
		panelPracas.setBorder(new TitledBorder(new LineBorder(new Color(184, 207, 229)), "Pra\u00E7as de alimenta\u00E7\u00E3o", TitledBorder.CENTER, TitledBorder.TOP, null, new Color(51, 51, 51)));
		
		panel.setBounds(12, 0, 766, 558);
		panelShoppings.setBounds(10, 10, 220, 80);
		btnAddShopping.setBounds(10, 45, 45, 25);
		btnRmShopping.setBounds(67, 45, 45, 25);
		comboBoxShop.setBounds(10, 15, 194, 24);
		panelPracas.setBounds(242, 10, 482, 534);
		btnEditarShopping.setBounds(124, 45, 80, 25);
		panelIdPraca.setBorder(new EtchedBorder(EtchedBorder.LOWERED, null, null));
		panelIdPraca.setBounds(15, 15, 145, 100);
		lblId.setBounds(5, 5, 31, 15);
		comboBoxId.setBounds(37, 5, 95, 24);
		btnAddId.setBounds(37, 35, 45, 25);
		btnRmId.setBounds(87, 35, 45, 25);
		btnEditarId.setBounds(37, 65, 95, 25);
		panelInfo.setBounds(165, 15, 175, 80);
		lblAreaTitle.setBounds(27, 5, 43, 15);
		lblArea.setBounds(78, 5, 92, 15);
		lblNumCadeirasTitle.setBounds(0, 20, 66, 15);
		lblNumCadeiras.setBounds(78, 20, 92, 15);
		lblNumMesasTitle.setBounds(18, 35, 66, 15);
		btnRestaurantes.setBounds(8, 55, 136, 25);
		lblNumMesas.setBounds(78, 35, 92, 15);
		
		comboBoxShop.setEnabled(false);
		comboBoxId.setEnabled(false);

		panelPracas.setLayout(null);
		panel.add(panelShoppings);
		panel.add(panelPracas);
		
		panelPracas.add(panelIdPraca);
		panelIdPraca.setLayout(null);
		panelIdPraca.add(lblId);
		panelIdPraca.add(comboBoxId);
		panelIdPraca.add(btnAddId);
		panelIdPraca.add(btnRmId);
		panelIdPraca.add(btnEditarId);
		
		panelPracas.add(panelInfo);
		panelInfo.setLayout(null);
		panelInfo.add(lblAreaTitle);
		panelInfo.add(lblArea);
		panelInfo.add(lblNumCadeirasTitle);
		panelInfo.add(lblNumCadeiras);
		panelInfo.add(lblNumMesasTitle);
		panelInfo.add(btnRestaurantes);
		
		panelInfo.add(lblNumMesas);
		panelShoppings.add(btnRmShopping);
		panelShoppings.add(comboBoxShop);
		panelShoppings.add(btnAddShopping);
		panelShoppings.add(btnEditarShopping);

		loadComboboxItems(comboBoxShop);
		loadPracas(comboBoxId, comboBoxShop.getSelectedItem().toString());
		loadInfos();
		addListeners();
	}
	
	private void addListeners() {
		btnAddShopping.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
				new AddShopping(comboBoxShop);
			}
		});
		
		btnRmShopping.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
				if(comboBoxShop.getItemCount() <= 0) {
					JOptionPane.showMessageDialog(null, "Ao menos um shopping deve estar cadastrado", "ERRO", JOptionPane.ERROR_MESSAGE);
				} else if(JOptionPane.showConfirmDialog(null, "Deseja realmente deletar " + comboBoxShop.getSelectedItem().toString() + "?\n TODOS OS DADOS DESSE SHOPPING SERÃO DELETADOS", "Confirmação", JOptionPane.OK_CANCEL_OPTION) == JOptionPane.OK_OPTION) {
					ConnectionDB.executeSQL("delete from shopping where nome = '" + comboBoxShop.getSelectedItem().toString() + "'");
					comboBoxShop.removeItem(comboBoxShop.getSelectedItem());
					if(comboBoxShop.getItemCount() <= 0) 
						comboBoxShop.setEnabled(false);
				}
			}
		});
		
		btnEditarShopping.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				String id = comboBoxShop.getSelectedItem().toString();
				if(comboBoxShop.getItemCount() <= 0) {
					JOptionPane.showMessageDialog(null, "Ao menos uma praça deve estar cadastrado", "ERRO", JOptionPane.ERROR_MESSAGE);
				}
				new AddShopping(comboBoxShop, id, ConnectionDB.getShoppingEnd(id), ConnectionDB.getShoppingTelefone(id));
			}
		});
		
		btnAddId.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				new AddPraca(comboBoxId, comboBoxShop.getSelectedItem().toString(), SQLJava.this);
				reorderCb(comboBoxId);
				loadInfos();
			}
		});
		
		btnRmId.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent arg0) {
				if(comboBoxId.getItemCount() <= 0) {
					JOptionPane.showMessageDialog(null, "Ao menos uma praça deve estar cadastrada", "ERRO", JOptionPane.ERROR_MESSAGE);
				} else if(JOptionPane.showConfirmDialog(null, "Deseja realmente deletar a praça " + ((Item)comboBoxId.getSelectedItem()).getIndex() + "?\nTODOS OS DADOS DESSA PRAÇA SERÃO DELETADOS", "Confirmação" , JOptionPane.WARNING_MESSAGE) == JOptionPane.OK_OPTION){
					ConnectionDB.executeSQL("delete from praca_alimentacao where id = " + ((Item)comboBoxId.getSelectedItem()).getId());
					comboBoxId.removeItem(comboBoxId.getSelectedItem());
					loadInfos();
					reorderCb(comboBoxId);
				}
			}
		});

		btnEditarId.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				if(comboBoxId.getSelectedItem() != null) {
					String id = String.valueOf(((Item)comboBoxId.getSelectedItem()).getId());
					new AddPraca(comboBoxId, comboBoxShop.getSelectedItem().toString(), ConnectionDB.getAreaPraca(id), ConnectionDB.getNumCadeirasPraca(id), ConnectionDB.getNumMesasPraca(id), SQLJava.this);
				} else {
					JOptionPane.showMessageDialog(null, "É necessário que ao menos uma praça de alimentação esteja cadastrada", "ERRO", JOptionPane.ERROR_MESSAGE);
				}
			}
		});
		
		comboBoxShop.addItemListener(new ItemListener() {
			
			@Override
			public void itemStateChanged(ItemEvent arg0) {
				loadPracas(comboBoxId, comboBoxShop.getSelectedItem().toString());
				loadInfos();
			}
		});
		
		comboBoxId.addItemListener(new ItemListener() {
			public void itemStateChanged(ItemEvent arg0) {
				loadInfos();
			}
		});
	}
	
	public void loadInfos() {
		if(comboBoxId.getItemCount() > 0 && comboBoxId.getSelectedItem() != null) {
			try {
				lblArea.setText(String.format("%.2f", Float.parseFloat(ConnectionDB.getAreaPraca( ((Item)comboBoxId.getSelectedItem()).getId()))) + " m²");				
			} catch (NumberFormatException ex) {
				lblArea.setText("Não definido");
			}
			lblNumCadeiras.setText(ConnectionDB.getNumCadeirasPraca(((Item)comboBoxId.getSelectedItem()).getId()));
			lblNumMesas.setText(ConnectionDB.getNumMesasPraca(((Item)comboBoxId.getSelectedItem()).getId()));
		} else {
			lblArea.setText("Não definido");
			lblNumCadeiras.setText("Não definido");
			lblNumMesas.setText("Não definido");
		}
	}

	private void loadComboboxItems(JComboBox<String> cb) {
		ArrayList<String> shoppings = ConnectionDB.getShoppings();
		for(String e : shoppings)
			cb.addItem(e);
		if(cb.getItemCount() > 0)
			cb.setEnabled(true);
	}
	
	private void loadPracas(JComboBox<Item> cb, String nome) {
		ArrayList<String> pracas = ConnectionDB.getPracas(nome);
		int i = cb.getItemCount(), j = 1; 
		while(i > 0) 
			cb.removeItem(cb.getItemAt(--i));
		for(String e: pracas) {
			cb.addItem(new Item(j, e));
			j++;
		}
		if(cb.getItemCount() <= 0) 
			cb.setEnabled(false); 
		else
			cb.setEnabled(true);
	}
	
	private void reorderCb(JComboBox<Item> cb) {
		int i = 0;
		while (i < cb.getItemCount()) {
			((Item)cb.getItemAt(i)).setIndex(++i);
		}
		if(cb.getItemCount() <= 0)
			cb.setEnabled(false);
	}
	
}
