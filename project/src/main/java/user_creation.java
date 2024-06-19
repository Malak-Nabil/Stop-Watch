abstract class user_creation implements user_info {
    private String name;
    private String email;
    private String password;

    public user_creation(String name, String email, String password) {
        this.name = name;
        this.email = email;
        this.password = password;
    }

    public String get_name() {
        return name;
    }

    public String get_email() {
        return email;
    }

    public String get_password() {
        return password;
    }

    abstract public String get_user_type();
}
