# Recebe dados do mundo externo (HTTP/JSON) e repassa.


from user_service import UserService
from user_repository import UserRepository

def create_user_endpoint(request_json):
    """
    Simula um endpoint HTTP que recebe um JSON.
    """

    # Extrai dados do "request"
    email = request_json.get("email")
    age = request_json.get("age")

    # Cria dependências reais
    repo = UserRepository()
    service = UserService(repo)

    # Chama a regra de negócio
    service.create_user(email, age)

    return {"status": "ok"}
