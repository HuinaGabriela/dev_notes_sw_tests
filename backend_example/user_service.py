# Não sabe que existe HTTP.
# Não sabe que existe banco.


class UserService:
    def __init__(self, repository):
        # Recebe o "driver" por injeção
        self.repository = repository

    def create_user(self, email, age):
        """
        Regra de negócio pura.
        """

        # Validação básica
        if not email or age is None:
            raise ValueError("Invalid data")

        # Regra 1: idade mínima
        if age < 18:
            raise ValueError("Underage user")

        # Regra 2: email não pode existir
        if self.repository.email_exists(email):
            raise ValueError("Email already exists")

        # Se passou em tudo, salva
        self.repository.save(email, age)
