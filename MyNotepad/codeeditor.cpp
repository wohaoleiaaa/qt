#include "codeeditor.h"
#include <QPainter>
#include <QTextBlock>
#include <QRegularExpression> // 添加 QRegularExpression 头文件
#include <QDesktopServices>   // 添加 QDesktopServices 头文件
#include <QUrl>               // 添加 QUrl 头文件
#include <QDebug>
CodeEditor::CodeEditor(QWidget *parent) : QPlainTextEdit(parent), isLineNumberAreaVisible(true) // 默认显示行号
{
    lineNumberArea = new LineNumberArea(this);

    connect(this, &CodeEditor::blockCountChanged, this, &CodeEditor::updateLineNumberAreaWidth);
    connect(this, &CodeEditor::updateRequest, this, &CodeEditor::updateLineNumberArea);
    connect(this, &CodeEditor::cursorPositionChanged, this, &CodeEditor::highlightCurrentLine);

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
}

void CodeEditor::setLineNumberAreaVisible(bool visible)
{
    isLineNumberAreaVisible = visible;
    lineNumberArea->setVisible(visible);
    updateLineNumberAreaWidth(0); // 更新边距
}

int CodeEditor::lineNumberAreaWidth()
{
    if (!isLineNumberAreaVisible) {
        return 0; // 如果行号区域隐藏，边距为 0
    }

    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

    return space;
}

void CodeEditor::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void CodeEditor::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

void CodeEditor::resizeEvent(QResizeEvent *event)
{
    QPlainTextEdit::resizeEvent(event);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void CodeEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(Qt::yellow).lighter(160);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}
void CodeEditor::mousePressEvent(QMouseEvent *event) {
    qDebug() << "mousePressEvent called"; // 调试信息

    // 先调用基类的 mousePressEvent，确保默认行为正常
    QPlainTextEdit::mousePressEvent(event);

    if (event->button() == Qt::LeftButton) {
        // 获取光标位置
        QTextCursor cursor = cursorForPosition(event->pos());
        if (!cursor.isNull()) {
            // 选中整行文本
            cursor.select(QTextCursor::LineUnderCursor);
            QString selectedText = cursor.selectedText();

            qDebug() << "Selected text:" << selectedText; // 调试信息

            // 正则表达式匹配 URL 和邮件地址
            QRegularExpression urlRegex(R"((https?://|www\.|ftp://|mailto:)[^\s]+)");
            QRegularExpression emailRegex(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");

            // 从选中的文本中提取完整的 URL 或邮件地址
            QRegularExpressionMatch urlMatch = urlRegex.match(selectedText);
            QRegularExpressionMatch emailMatch = emailRegex.match(selectedText);

            if (urlMatch.hasMatch()) {
                QUrl url(urlMatch.captured());
                if (url.scheme().isEmpty()) {
                    url.setScheme("http");  // 默认使用 http 协议
                }

                qDebug() << "Attempting to open URL:" << url.toString(); // 调试信息

                // 调用系统默认程序打开链接
                if (!QDesktopServices::openUrl(url)) {
                    qDebug() << "Failed to open URL:" << url.toString(); // 调试信息
                }
            } else if (emailMatch.hasMatch()) {
                QUrl url("mailto:" + emailMatch.captured());

                qDebug() << "Attempting to open email:" << url.toString(); // 调试信息

                // 调用系统默认程序打开邮件地址
                if (!QDesktopServices::openUrl(url)) {
                    qDebug() << "Failed to open email:" << url.toString(); // 调试信息
                }
            } else {
                qDebug() << "Selected text is not a valid URL or email:" << selectedText; // 调试信息
            }
        }
    }
}
void CodeEditor::highlightLinks() {
    QTextDocument *document = this->document();
    QTextCursor cursor(document);

    // 清除之前的高亮
    QTextCharFormat plainFormat;
    cursor.select(QTextCursor::Document);
    cursor.mergeCharFormat(plainFormat);

    // 高亮 URL
    QRegularExpression urlRegex(R"((https?://|www\.|ftp://|mailto:)[^\s]+)");
    QTextCharFormat urlFormat;
    urlFormat.setForeground(Qt::blue);
    urlFormat.setFontUnderline(true);

    cursor = QTextCursor(document);
    while (!cursor.isNull() && !cursor.atEnd()) {
        cursor = document->find(urlRegex, cursor);
        if (!cursor.isNull()) {
            cursor.mergeCharFormat(urlFormat);
        }
    }

    // 高亮邮件地址
    QRegularExpression emailRegex(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    QTextCharFormat emailFormat;
    emailFormat.setForeground(Qt::blue);
    emailFormat.setFontUnderline(true);

    cursor = QTextCursor(document);
    while (!cursor.isNull() && !cursor.atEnd()) {
        cursor = document->find(emailRegex, cursor);
        if (!cursor.isNull()) {
            cursor.mergeCharFormat(emailFormat);
        }
    }
}
