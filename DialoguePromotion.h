#pragma once

#pragma once
#pragma warning(disable: 4828)
#pragma warning(push, 0)
#include <QDialog>
#include <QComboBox>
#include <QMessageBox>
#include <QBoxLayout>
#include <QPushButton>
#include <QString>
#include <QLabel>
#pragma warning(pop)

namespace Vue {

	class DialoguePromotion : public QDialog {
	public:
		DialoguePromotion(QWidget* parent = nullptr);
		~DialoguePromotion() = default;

		QString obtenirPromotion() const;

	private:
		QComboBox* choixPosition_;
	};

}