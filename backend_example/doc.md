No terminal, dentro da pasta backend_example:
python -m venv venv

Linux / macOS
source venv/bin/activate

Windows:
venv\Scripts\activate


Instalar pytest:
pip install pytest

Rodar os testes:
pytest
ou python -m pytest

saida esperada algo tipo:
3 passed in 0.02s

Rodar um teste específico:
pytest tests/test_user_service.py::test_should_fail_if_underage


