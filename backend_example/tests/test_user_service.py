import pytest
from unittest.mock import Mock
from user_service import UserService


def test_should_fail_if_underage():
    repo = Mock()
    service = UserService(repo)

    with pytest.raises(ValueError):
        service.create_user("a@a.com", 17)


def test_should_fail_if_email_exists():
    repo = Mock()
    repo.email_exists.return_value = True

    service = UserService(repo)

    with pytest.raises(ValueError):
        service.create_user("a@a.com", 25)


def test_should_save_if_valid():
    repo = Mock()
    repo.email_exists.return_value = False

    service = UserService(repo)

    service.create_user("a@a.com", 25)

    repo.save.assert_called_once_with("a@a.com", 25)
