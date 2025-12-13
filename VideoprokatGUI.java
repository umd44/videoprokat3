package videoprokat;

import javax.swing.*;
import javax.swing.border.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.util.List;

/**
 * GUI приложение для системы видеопроката с графическим интерфейсом.
 */
public class VideoprokatGUI extends JFrame {

    private User currentUser = null;
    private Catalog catalog = new CatalogReal();
    private RentalManager rentalManager = new RentalManagerReal();
    private ReportGenerator reportGenerator = new ReportGeneratorReal();
    private List<Client> clients = new ArrayList<>();
    private List<User> users = new ArrayList<>();
    private int nextClientId = 1001;
    private int nextInventoryNumber = 2001;

    private JPanel mainPanel;
    private CardLayout cardLayout;

    public static void main(String[] args) {
        try {
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        } catch (Exception e) {
            e.printStackTrace();
        }

        SwingUtilities.invokeLater(() -> {
            VideoprokatGUI gui = new VideoprokatGUI();
            gui.setVisible(true);
        });
    }

    public VideoprokatGUI() {
        initializeSystem();
        setupMainFrame();
        showLoginScreen();
    }

    private void initializeSystem() {
        // Создание пользователей
        users.add(new UserReal(1, "operator", "1234", "Operator", "Иванов Иван Иванович"));
        users.add(new UserReal(2, "senior", "5678", "Senior Operator", "Петров Петр Петрович"));
        users.add(new UserReal(3, "admin", "admin", "Administrator", "Сидоров Сидор Сидорович"));

        // Создание тестовых клиентов
        ClientReal client1 = new ClientReal(nextClientId++, "Алексей", "Смирнов", "+7-925-123-45-67");
        client1.setMiddleName("Николаевич");
        client1.setEmail("smirnov@mail.ru");
        client1.setPassport("4512", "789456");
        client1.setBirthDate("1990-05-15");
        client1.setRegistrationDate("2024-01-10");
        client1.addBonusPoints(50);
        clients.add(client1);

        ClientReal client2 = new ClientReal(nextClientId++, "Мария", "Иванова", "+7-916-987-65-43");
        client2.setMiddleName("Петровна");
        client2.setEmail("ivanova@gmail.com");
        client2.setPassport("4513", "654321");
        client2.setBirthDate("1995-08-22");
        client2.setRegistrationDate("2024-03-15");
        client2.addBonusPoints(120);
        clients.add(client2);

        // Добавление видеоносителей
        addMovieToCatalog("Матрица", "Blu-ray", "Фантастика", 1999, "Вачовски", "16+", 
            "Программист Томас Андерсон узнаёт правду о реальности", 100.0, 800.0);
        addMovieToCatalog("Интерстеллар", "Blu-ray", "Фантастика", 2014, "Кристофер Нолан", "12+",
            "Команда исследователей отправляется в космос", 120.0, 900.0);
        addMovieToCatalog("Зеленая миля", "DVD", "Драма", 1999, "Фрэнк Дарабонт", "16+",
            "История о начальнике охраны в тюрьме", 80.0, 500.0);
        addMovieToCatalog("Властелин колец", "Blu-ray", "Фэнтези", 2001, "Питер Джексон", "12+",
            "Эпическая история о Средиземье", 110.0, 850.0);
        addMovieToCatalog("Чужой", "DVD", "Ужасы", 1979, "Ридли Скотт", "18+",
            "Команда космического корабля встречает внеземную форму жизни", 90.0, 600.0);
        addMovieToCatalog("Аватар", "Blu-ray", "Фэнтези", 2009, "Джеймс Кэмерон", "12+",
            "История о планете Пандора", 130.0, 950.0);
        addMovieToCatalog("Титаник", "DVD", "Мелодрама", 1997, "Джеймс Кэмерон", "12+",
            "История любви на борту легендарного корабля", 70.0, 450.0);
    }

    private void addMovieToCatalog(String title, String type, String genre, int year,
                                    String director, String ageRating, String description,
                                    double pricePerDay, double fullPrice) {
        VideoCarrierReal movie = new VideoCarrierReal(nextInventoryNumber++, title, type, genre,
            pricePerDay, fullPrice);
        movie.setReleaseYear(year);
        movie.setDirector(director);
        movie.setAgeRating(ageRating);
        movie.setDescription(description);
        catalog.addItem(movie);
    }

    private void setupMainFrame() {
        setTitle("Информационная система видеопроката");
        setSize(1200, 800);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        cardLayout = new CardLayout();
        mainPanel = new JPanel(cardLayout);
        add(mainPanel);
    }

    private void showLoginScreen() {
        JPanel loginPanel = new JPanel(new GridBagLayout());
        loginPanel.setBackground(new Color(240, 240, 245));
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(10, 10, 10, 10);

        // Заголовок
        JLabel titleLabel = new JLabel("Система видеопроката");
        titleLabel.setFont(new Font("Arial", Font.BOLD, 28));
        titleLabel.setForeground(new Color(0, 102, 204));
        gbc.gridx = 0;
        gbc.gridy = 0;
        gbc.gridwidth = 2;
        gbc.anchor = GridBagConstraints.CENTER;
        loginPanel.add(titleLabel, gbc);

        gbc.gridwidth = 1;
        gbc.anchor = GridBagConstraints.EAST;

        // Логин
        gbc.gridy = 1;
        loginPanel.add(new JLabel("Логин:"), gbc);

        JTextField usernameField = new JTextField(20);
        gbc.gridx = 1;
        gbc.anchor = GridBagConstraints.WEST;
        loginPanel.add(usernameField, gbc);

        // Пароль
        gbc.gridx = 0;
        gbc.gridy = 2;
        gbc.anchor = GridBagConstraints.EAST;
        loginPanel.add(new JLabel("Пароль:"), gbc);

        JPasswordField passwordField = new JPasswordField(20);
        gbc.gridx = 1;
        gbc.anchor = GridBagConstraints.WEST;
        loginPanel.add(passwordField, gbc);

        // Подсказка
        JTextArea hintArea = new JTextArea(
            "Доступные учетные записи:\n" +
            "operator / 1234 - Оператор\n" +
            "senior / 5678 - Старший оператор\n" +
            "admin / admin - Администратор"
        );
        hintArea.setEditable(false);
        hintArea.setBackground(new Color(255, 255, 220));
        hintArea.setBorder(BorderFactory.createLineBorder(Color.GRAY));
        hintArea.setFont(new Font("Monospaced", Font.PLAIN, 11));
        gbc.gridx = 0;
        gbc.gridy = 3;
        gbc.gridwidth = 2;
        gbc.anchor = GridBagConstraints.CENTER;
        loginPanel.add(hintArea, gbc);

        // Кнопка входа
        JButton loginButton = new JButton("Войти");
        loginButton.setPreferredSize(new Dimension(200, 35));
        loginButton.setBackground(new Color(0, 153, 76));
        loginButton.setForeground(Color.WHITE);
        loginButton.setFont(new Font("Arial", Font.BOLD, 14));
        gbc.gridy = 4;
        loginPanel.add(loginButton, gbc);

        loginButton.addActionListener(e -> {
            String username = usernameField.getText();
            String password = new String(passwordField.getPassword());

            for (User user : users) {
                if (user.getUsername().equals(username) && user.checkPassword(password)) {
                    currentUser = user;
                    showMainMenu();
                    return;
                }
            }

            JOptionPane.showMessageDialog(this, 
                "Неверный логин или пароль!", 
                "Ошибка входа", 
                JOptionPane.ERROR_MESSAGE);
        });

        // Enter для входа
        ActionListener enterAction = e -> loginButton.doClick();
        usernameField.addActionListener(enterAction);
        passwordField.addActionListener(enterAction);

        mainPanel.add(loginPanel, "LOGIN");
        cardLayout.show(mainPanel, "LOGIN");
    }

    private void showMainMenu() {
        JPanel menuPanel = new JPanel(new BorderLayout());
        menuPanel.setBackground(Color.WHITE);

        // Верхняя панель с информацией о пользователе
        JPanel headerPanel = new JPanel(new BorderLayout());
        headerPanel.setBackground(new Color(0, 102, 204));
        headerPanel.setBorder(BorderFactory.createEmptyBorder(10, 15, 10, 15));

        JLabel userLabel = new JLabel(currentUser.getFullName() + " (" + currentUser.getRole() + ")");
        userLabel.setForeground(Color.WHITE);
        userLabel.setFont(new Font("Arial", Font.BOLD, 14));
        headerPanel.add(userLabel, BorderLayout.WEST);

        JButton logoutButton = new JButton("Выход");
        logoutButton.addActionListener(e -> {
            currentUser = null;
            showLoginScreen();
            cardLayout.show(mainPanel, "LOGIN");
        });
        headerPanel.add(logoutButton, BorderLayout.EAST);

        menuPanel.add(headerPanel, BorderLayout.NORTH);

        // Центральная панель с кнопками меню
        JPanel buttonsPanel = new JPanel(new GridLayout(3, 3, 20, 20));
        buttonsPanel.setBorder(BorderFactory.createEmptyBorder(30, 30, 30, 30));
        buttonsPanel.setBackground(Color.WHITE);

        // Кнопки меню
        addMenuButton(buttonsPanel, "📀 Видеоносители", 
            "Управление каталогом фильмов", e -> showVideoCarriersMenu());
        
        addMenuButton(buttonsPanel, "👥 Клиенты", 
            "Управление клиентской базой", e -> showClientsMenu());
        
        addMenuButton(buttonsPanel, "🎬 Оформление аренды", 
            "Создание новой аренды", e -> showCreateRentalDialog());
        
        addMenuButton(buttonsPanel, "↩️ Обработка возврата", 
            "Возврат носителей", e -> showProcessReturnDialog());
        
        addMenuButton(buttonsPanel, "📊 Отчеты", 
            "Статистика и отчетность", e -> showReportsMenu());
        
        if (currentUser.hasPermission("manage_users")) {
            addMenuButton(buttonsPanel, "👤 Пользователи", 
                "Управление пользователями", e -> showUsersDialog());
        } else {
            JButton disabledBtn = createStyledButton("👤 Пользователи", "Недоступно");
            disabledBtn.setEnabled(false);
            buttonsPanel.add(disabledBtn);
        }

        addMenuButton(buttonsPanel, "ℹ️ О системе", 
            "Информация о программе", e -> showAboutDialog());

        menuPanel.add(buttonsPanel, BorderLayout.CENTER);

        mainPanel.add(menuPanel, "MENU");
        cardLayout.show(mainPanel, "MENU");
    }

    private void addMenuButton(JPanel panel, String title, String description, ActionListener action) {
        JButton button = createStyledButton(title, description);
        button.addActionListener(action);
        panel.add(button);
    }

    private JButton createStyledButton(String title, String description) {
        JButton button = new JButton("<html><center><b>" + title + "</b><br><small>" + description + "</small></center></html>");
        button.setPreferredSize(new Dimension(200, 100));
        button.setFont(new Font("Arial", Font.PLAIN, 14));
        button.setBackground(new Color(240, 248, 255));
        button.setBorder(BorderFactory.createCompoundBorder(
            BorderFactory.createLineBorder(new Color(0, 102, 204), 2),
            BorderFactory.createEmptyBorder(10, 10, 10, 10)
        ));
        button.setFocusPainted(false);
        
        button.addMouseListener(new MouseAdapter() {
            public void mouseEntered(MouseEvent e) {
                button.setBackground(new Color(230, 240, 255));
            }
            public void mouseExited(MouseEvent e) {
                button.setBackground(new Color(240, 248, 255));
            }
        });
        
        return button;
    }

    private void showVideoCarriersMenu() {
        JDialog dialog = new JDialog(this, "Управление видеоносителями", true);
        dialog.setSize(1000, 600);
        dialog.setLocationRelativeTo(this);

        JPanel panel = new JPanel(new BorderLayout(10, 10));
        panel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));

        // Таблица носителей
        String[] columns = {"№", "Название", "Тип", "Жанр", "Год", "Режиссер", "Рейтинг", "Цена/день", "Статус"};
        DefaultTableModel model = new DefaultTableModel(columns, 0) {
            @Override
            public boolean isCellEditable(int row, int column) {
                return false;
            }
        };

        List<VideoCarrier> items = catalog.getAllItems();
        for (VideoCarrier item : items) {
            model.addRow(new Object[]{
                item.getInventoryNumber(),
                item.getTitle(),
                item.getCarrierType(),
                item.getGenre(),
                item.getReleaseYear(),
                item.getDirector(),
                item.getAgeRating(),
                String.format("%.2f руб", item.getRentalPricePerDay()),
                getStatusRussian(item.getStatus())
            });
        }

        JTable table = new JTable(model);
        table.setRowHeight(25);
        table.getColumnModel().getColumn(1).setPreferredWidth(200);
        JScrollPane scrollPane = new JScrollPane(table);

        panel.add(scrollPane, BorderLayout.CENTER);

        // Панель кнопок
        JPanel buttonPanel = new JPanel(new FlowLayout(FlowLayout.RIGHT));
        
        JButton searchButton = new JButton("Поиск");
        searchButton.addActionListener(e -> showSearchDialog());
        buttonPanel.add(searchButton);

        if (currentUser.hasPermission("edit_items")) {
            JButton addButton = new JButton("Добавить носитель");
            addButton.addActionListener(e -> {
                showAddCarrierDialog();
                dialog.dispose();
                showVideoCarriersMenu();
            });
            buttonPanel.add(addButton);
        }

        JButton statsButton = new JButton("Статистика");
        statsButton.addActionListener(e -> showStatisticsDialog());
        buttonPanel.add(statsButton);

        JButton closeButton = new JButton("Закрыть");
        closeButton.addActionListener(e -> dialog.dispose());
        buttonPanel.add(closeButton);

        panel.add(buttonPanel, BorderLayout.SOUTH);

        dialog.add(panel);
        dialog.setVisible(true);
    }

    private void showSearchDialog() {
        String[] options = {"По названию", "По жанру", "По режиссеру", "По году", "По типу носителя", "Только доступные"};
        String choice = (String) JOptionPane.showInputDialog(this, 
            "Выберите критерий поиска:", "Поиск",
            JOptionPane.QUESTION_MESSAGE, null, options, options[0]);

        if (choice == null) return;

        List<VideoCarrier> results = new ArrayList<>();

        switch (choice) {
            case "По названию":
                String title = JOptionPane.showInputDialog(this, "Введите название:");
                if (title != null) results = catalog.findItemsByTitle(title);
                break;
            case "По жанру":
                String genre = JOptionPane.showInputDialog(this, "Введите жанр:");
                if (genre != null) results = catalog.findItemsByGenre(genre);
                break;
            case "По режиссеру":
                String director = JOptionPane.showInputDialog(this, "Введите имя режиссера:");
                if (director != null) results = catalog.findItemsByDirector(director);
                break;
            case "По году":
                String yearStr = JOptionPane.showInputDialog(this, "Введите год:");
                if (yearStr != null) {
                    try {
                        results = catalog.findItemsByYear(Integer.parseInt(yearStr));
                    } catch (NumberFormatException ex) {
                        JOptionPane.showMessageDialog(this, "Неверный формат года!");
                    }
                }
                break;
            case "По типу носителя":
                String type = JOptionPane.showInputDialog(this, "Введите тип (DVD/Blu-ray):");
                if (type != null) results = catalog.findItemsByCarrierType(type);
                break;
            case "Только доступные":
                results = catalog.getAvailableItems();
                break;
        }

        showSearchResults(results);
    }

    private void showSearchResults(List<VideoCarrier> results) {
        JDialog dialog = new JDialog(this, "Результаты поиска", true);
        dialog.setSize(900, 500);
        dialog.setLocationRelativeTo(this);

        JPanel panel = new JPanel(new BorderLayout(10, 10));
        panel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));

        if (results.isEmpty()) {
            panel.add(new JLabel("Ничего не найдено"), BorderLayout.CENTER);
        } else {
            String[] columns = {"№", "Название", "Тип", "Жанр", "Год", "Цена/день", "Статус"};
            DefaultTableModel model = new DefaultTableModel(columns, 0);

            for (VideoCarrier item : results) {
                model.addRow(new Object[]{
                    item.getInventoryNumber(),
                    item.getTitle(),
                    item.getCarrierType(),
                    item.getGenre(),
                    item.getReleaseYear(),
                    String.format("%.2f руб", item.getRentalPricePerDay()),
                    getStatusRussian(item.getStatus())
                });
            }

            JTable table = new JTable(model);
            table.setRowHeight(25);
            panel.add(new JScrollPane(table), BorderLayout.CENTER);

            JLabel countLabel = new JLabel("Найдено: " + results.size());
            panel.add(countLabel, BorderLayout.NORTH);
        }

        JButton closeButton = new JButton("Закрыть");
        closeButton.addActionListener(e -> dialog.dispose());
        panel.add(closeButton, BorderLayout.SOUTH);

        dialog.add(panel);
        dialog.setVisible(true);
    }

    private void showAddCarrierDialog() {
        JDialog dialog = new JDialog(this, "Добавление носителя", true);
        dialog.setSize(500, 600);
        dialog.setLocationRelativeTo(this);

        JPanel panel = new JPanel(new GridBagLayout());
        panel.setBorder(BorderFactory.createEmptyBorder(15, 15, 15, 15));
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(5, 5, 5, 5);
        gbc.fill = GridBagConstraints.HORIZONTAL;

        JTextField titleField = new JTextField(20);
        JTextField typeField = new JTextField(20);
        JTextField genreField = new JTextField(20);
        JTextField yearField = new JTextField(20);
        JTextField directorField = new JTextField(20);
        JTextField ratingField = new JTextField(20);
        JTextField priceField = new JTextField(20);
        JTextField fullPriceField = new JTextField(20);
        JTextArea descArea = new JTextArea(3, 20);
        descArea.setLineWrap(true);

        addFormField(panel, gbc, 0, "Название:", titleField);
        addFormField(panel, gbc, 1, "Тип (DVD/Blu-ray):", typeField);
        addFormField(panel, gbc, 2, "Жанр:", genreField);
        addFormField(panel, gbc, 3, "Год выпуска:", yearField);
        addFormField(panel, gbc, 4, "Режиссер:", directorField);
        addFormField(panel, gbc, 5, "Возрастной рейтинг:", ratingField);
        addFormField(panel, gbc, 6, "Цена проката (руб/день):", priceField);
        addFormField(panel, gbc, 7, "Полная стоимость:", fullPriceField);
        
        gbc.gridy = 8;
        gbc.gridx = 0;
        panel.add(new JLabel("Описание:"), gbc);
        gbc.gridx = 1;
        panel.add(new JScrollPane(descArea), gbc);

        JButton saveButton = new JButton("Сохранить");
        JButton cancelButton = new JButton("Отмена");

        saveButton.addActionListener(e -> {
            try {
                addMovieToCatalog(
                    titleField.getText(),
                    typeField.getText(),
                    genreField.getText(),
                    Integer.parseInt(yearField.getText()),
                    directorField.getText(),
                    ratingField.getText(),
                    descArea.getText(),
                    Double.parseDouble(priceField.getText()),
                    Double.parseDouble(fullPriceField.getText())
                );
                JOptionPane.showMessageDialog(dialog, "Носитель успешно добавлен!");
                dialog.dispose();
            } catch (Exception ex) {
                JOptionPane.showMessageDialog(dialog, "Ошибка: " + ex.getMessage());
            }
        });

        cancelButton.addActionListener(e -> dialog.dispose());

        JPanel buttonPanel = new JPanel(new FlowLayout(FlowLayout.RIGHT));
        buttonPanel.add(saveButton);
        buttonPanel.add(cancelButton);

        gbc.gridy = 9;
        gbc.gridx = 0;
        gbc.gridwidth = 2;
        panel.add(buttonPanel, gbc);

        dialog.add(panel);
        dialog.setVisible(true);
    }

    private void addFormField(JPanel panel, GridBagConstraints gbc, int row, String label, JComponent field) {
        gbc.gridy = row;
        gbc.gridx = 0;
        gbc.anchor = GridBagConstraints.EAST;
        panel.add(new JLabel(label), gbc);
        
        gbc.gridx = 1;
        gbc.anchor = GridBagConstraints.WEST;
        panel.add(field, gbc);
    }

    private void showStatisticsDialog() {
        Map<String, Integer> stats = catalog.getStatistics();
        
        String message = String.format(
            "Статистика каталога:\n\n" +
            "Всего носителей: %d\n" +
            "Доступных: %d\n" +
            "Арендованных: %d\n" +
            "На реставрации: %d\n" +
            "Списанных: %d\n\n" +
            "Топ-5 популярных носителей:\n",
            stats.get("total"), stats.get("available"), stats.get("rented"),
            stats.get("maintenance"), stats.get("written_off")
        );

        List<VideoCarrier> top = catalog.getTopRentedItems(5);
        for (int i = 0; i < top.size(); i++) {
            VideoCarrier item = top.get(i);
            message += String.format("%d. %s - %d аренд\n", 
                i + 1, item.getTitle(), item.getTotalRentals());
        }

        JOptionPane.showMessageDialog(this, message, "Статистика", JOptionPane.INFORMATION_MESSAGE);
    }

    private void showClientsMenu() {
        JDialog dialog = new JDialog(this, "Управление клиентами", true);
        dialog.setSize(1000, 600);
        dialog.setLocationRelativeTo(this);

        JPanel panel = new JPanel(new BorderLayout(10, 10));
        panel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));

        String[] columns = {"ID", "ФИО", "Телефон", "Email", "Бонусы", "Статус"};
        DefaultTableModel model = new DefaultTableModel(columns, 0) {
            @Override
            public boolean isCellEditable(int row, int column) {
                return false;
            }
        };

        for (Client client : clients) {
            String fullName = client.getLastName() + " " + client.getFirstName() + " " + client.getMiddleName();
            model.addRow(new Object[]{
                client.getClientId(),
                fullName,
                client.getPhoneNumber(),
                client.getEmail(),
                client.getBonusPoints(),
                client.isBlacklisted() ? "БЛОКИРОВАН" : "Активен"
            });
        }

        JTable table = new JTable(model);
        table.setRowHeight(25);
        JScrollPane scrollPane = new JScrollPane(table);
        panel.add(scrollPane, BorderLayout.CENTER);

        JPanel buttonPanel = new JPanel(new FlowLayout(FlowLayout.RIGHT));
        
        JButton registerButton = new JButton("Регистрация клиента");
        registerButton.addActionListener(e -> {
            showRegisterClientDialog();
            dialog.dispose();
            showClientsMenu();
        });
        buttonPanel.add(registerButton);

        if (currentUser.hasPermission("edit_client_status")) {
            JButton blockButton = new JButton("Блокировка/Разблокировка");
            blockButton.addActionListener(e -> showBlockClientDialog());
            buttonPanel.add(blockButton);
        }

        JButton closeButton = new JButton("Закрыть");
        closeButton.addActionListener(e -> dialog.dispose());
        buttonPanel.add(closeButton);

        panel.add(buttonPanel, BorderLayout.SOUTH);

        dialog.add(panel);
        dialog.setVisible(true);
    }

    private void showRegisterClientDialog() {
        JDialog dialog = new JDialog(this, "Регистрация клиента", true);
        dialog.setSize(500, 550);
        dialog.setLocationRelativeTo(this);

        JPanel panel = new JPanel(new GridBagLayout());
        panel.setBorder(BorderFactory.createEmptyBorder(15, 15, 15, 15));
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(5, 5, 5, 5);
        gbc.fill = GridBagConstraints.HORIZONTAL;

        JTextField lastNameField = new JTextField(20);
        JTextField firstNameField = new JTextField(20);
        JTextField middleNameField = new JTextField(20);
        JTextField phoneField = new JTextField(20);
        JTextField emailField = new JTextField(20);
        JTextField passportSeriesField = new JTextField(20);
        JTextField passportNumberField = new JTextField(20);
        JTextField birthDateField = new JTextField(20);
        JTextField addressField = new JTextField(20);

        addFormField(panel, gbc, 0, "Фамилия:", lastNameField);
        addFormField(panel, gbc, 1, "Имя:", firstNameField);
        addFormField(panel, gbc, 2, "Отчество:", middleNameField);
        addFormField(panel, gbc, 3, "Телефон:", phoneField);
        addFormField(panel, gbc, 4, "Email:", emailField);
        addFormField(panel, gbc, 5, "Серия паспорта:", passportSeriesField);
        addFormField(panel, gbc, 6, "Номер паспорта:", passportNumberField);
        addFormField(panel, gbc, 7, "Дата рождения (ГГГГ-ММ-ДД):", birthDateField);
        addFormField(panel, gbc, 8, "Адрес:", addressField);

        JButton saveButton = new JButton("Сохранить");
        JButton cancelButton = new JButton("Отмена");

        saveButton.addActionListener(e -> {
            ClientReal newClient = new ClientReal(nextClientId++, 
                firstNameField.getText(), lastNameField.getText(), phoneField.getText());
            newClient.setMiddleName(middleNameField.getText());
            newClient.setEmail(emailField.getText());
            newClient.setPassport(passportSeriesField.getText(), passportNumberField.getText());
            newClient.setBirthDate(birthDateField.getText());
            newClient.setAddress(addressField.getText());
            newClient.setRegistrationDate("2025-01-18");

            clients.add(newClient);
            JOptionPane.showMessageDialog(dialog, "Клиент зарегистрирован! ID: " + newClient.getClientId());
            dialog.dispose();
        });

        cancelButton.addActionListener(e -> dialog.dispose());

        JPanel buttonPanel = new JPanel(new FlowLayout(FlowLayout.RIGHT));
        buttonPanel.add(saveButton);
        buttonPanel.add(cancelButton);

        gbc.gridy = 9;
        gbc.gridx = 0;
        gbc.gridwidth = 2;
        panel.add(buttonPanel, gbc);

        dialog.add(panel);
        dialog.setVisible(true);
    }

    private void showBlockClientDialog() {
        String idStr = JOptionPane.showInputDialog(this, "Введите ID клиента:");
        if (idStr == null) return;

        try {
            int id = Integer.parseInt(idStr);
            Client client = findClientById(id);
            
            if (client == null) {
                JOptionPane.showMessageDialog(this, "Клиент не найден!");
                return;
            }

            String message = "Клиент: " + client.getLastName() + " " + client.getFirstName() + "\n" +
                "Текущий статус: " + (client.isBlacklisted() ? "ЗАБЛОКИРОВАН" : "Активен");

            if (client.isBlacklisted()) {
                int result = JOptionPane.showConfirmDialog(this, 
                    message + "\n\nРазблокировать клиента?", 
                    "Разблокировка", JOptionPane.YES_NO_OPTION);
                
                if (result == JOptionPane.YES_OPTION) {
                    client.setBlacklisted(false);
                    client.setBlacklistReason("");
                    JOptionPane.showMessageDialog(this, "Клиент разблокирован!");
                }
            } else {
                int result = JOptionPane.showConfirmDialog(this, 
                    message + "\n\nЗаблокировать клиента?", 
                    "Блокировка", JOptionPane.YES_NO_OPTION);
                
                if (result == JOptionPane.YES_OPTION) {
                    String reason = JOptionPane.showInputDialog(this, "Причина блокировки:");
                    if (reason != null) {
                        client.setBlacklisted(true);
                        client.setBlacklistReason(reason);
                        JOptionPane.showMessageDialog(this, "Клиент заблокирован!");
                    }
                }
            }
        } catch (NumberFormatException ex) {
            JOptionPane.showMessageDialog(this, "Неверный формат ID!");
        }
    }

    private void showCreateRentalDialog() {
        JOptionPane.showMessageDialog(this, 
            "Функция оформления аренды\n" +
            "Введите ID клиента, выберите носители и укажите срок аренды.\n" +
            "Для полной демонстрации используйте консольную версию.",
            "Оформление аренды", JOptionPane.INFORMATION_MESSAGE);
    }

    private void showProcessReturnDialog() {
        List<Rental> activeRentals = rentalManager.getActiveRentals();
        
        if (activeRentals.isEmpty()) {
            JOptionPane.showMessageDialog(this, "Нет активных аренд!");
            return;
        }

        String[] rentalIds = activeRentals.stream()
            .map(r -> "Аренда #" + r.getRentalId() + " - " + 
                r.getClient().getLastName() + " " + r.getClient().getFirstName())
            .toArray(String[]::new);

        String selected = (String) JOptionPane.showInputDialog(this,
            "Выберите аренду для возврата:",
            "Обработка возврата",
            JOptionPane.QUESTION_MESSAGE,
            null,
            rentalIds,
            rentalIds[0]);

        if (selected != null) {
            JOptionPane.showMessageDialog(this, 
                "Функция обработки возврата\n" +
                "Укажите просрочку и повреждения.\n" +
                "Для полной демонстрации используйте консольную версию.",
                "Обработка возврата", JOptionPane.INFORMATION_MESSAGE);
        }
    }

    private void showReportsMenu() {
        String[] options = {
            "Финансовый отчет",
            "Отчет по клиентам",
            "Топ популярных носителей",
            "Отчет по просрочкам",
            "Дашборд текущего дня"
        };

        String choice = (String) JOptionPane.showInputDialog(this,
            "Выберите тип отчета:",
            "Отчеты и статистика",
            JOptionPane.QUESTION_MESSAGE,
            null,
            options,
            options[0]);

        if (choice == null) return;

        String report = "";
        switch (choice) {
            case "Финансовый отчет":
                report = reportGenerator.generateFinancialReport("2025-01-01", "2025-12-31");
                break;
            case "Отчет по клиентам":
                report = reportGenerator.generateClientReport(clients);
                break;
            case "Топ популярных носителей":
                report = reportGenerator.generateTopItemsReport(catalog.getTopRentedItems(10));
                break;
            case "Отчет по просрочкам":
                report = reportGenerator.generateOverdueReport(rentalManager.getOverdueRentals("2025-01-18"));
                break;
            case "Дашборд текущего дня":
                if (!currentUser.hasPermission("view_all_reports")) {
                    JOptionPane.showMessageDialog(this, "Недостаточно прав!");
                    return;
                }
                report = reportGenerator.generateDailyDashboard(
                    rentalManager.getActiveRentals().size(),
                    0, 0.0, clients.size(),
                    catalog.getStatistics()
                );
                break;
        }

        JTextArea textArea = new JTextArea(report);
        textArea.setEditable(false);
        textArea.setFont(new Font("Monospaced", Font.PLAIN, 12));
        JScrollPane scrollPane = new JScrollPane(textArea);
        scrollPane.setPreferredSize(new Dimension(600, 400));
        
        JOptionPane.showMessageDialog(this, scrollPane, choice, JOptionPane.INFORMATION_MESSAGE);
    }

    private void showUsersDialog() {
        String message = "Пользователи системы:\n\n";
        for (User user : users) {
            message += String.format("ID: %d | Логин: %s | ФИО: %s | Роль: %s\n",
                user.getUserId(), user.getUsername(), user.getFullName(), user.getRole());
        }
        
        JOptionPane.showMessageDialog(this, message, "Управление пользователями", 
            JOptionPane.INFORMATION_MESSAGE);
    }

    private void showAboutDialog() {
        String message = "Информационная система видеопроката\n" +
            "Версия 2.0 (GUI)\n\n" +
            "Локальная многопользовательская система\n" +
            "для автоматизации работы пункта проката\n" +
            "фильмов и игровых консолей.\n\n" +
            "© 2025 Все права защищены";
        
        JOptionPane.showMessageDialog(this, message, "О системе", 
            JOptionPane.INFORMATION_MESSAGE);
    }

    private String getStatusRussian(String status) {
        switch (status) {
            case "available": return "Доступен";
            case "rented": return "Арендован";
            case "maintenance": return "Реставрация";
            case "written_off": return "Списан";
            default: return status;
        }
    }

    private Client findClientById(int id) {
        for (Client client : clients) {
            if (client.getClientId() == id) return client;
        }
        return null;
    }
}
