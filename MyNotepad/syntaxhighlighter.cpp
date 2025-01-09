#include "syntaxhighlighter.h"

SyntaxHighlighter::SyntaxHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent) {
    // 关键字格式
    keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);

    // 单行注释格式
    singleLineCommentFormat.setForeground(Qt::darkGreen);

    // 多行注释格式
    multiLineCommentFormat.setForeground(Qt::darkGreen);

    // 字符串格式
    quotationFormat.setForeground(Qt::darkRed);

    // 函数格式
    functionFormat.setForeground(Qt::blue);

    // 定义关键字
    QStringList keywordPatterns;
    keywordPatterns << "\\bchar\\b" << "\\bclass\\b" << "\\bconst\\b"
                    << "\\bdouble\\b" << "\\benum\\b" << "\\bexplicit\\b"
                    << "\\bfriend\\b" << "\\binline\\b" << "\\bint\\b"
                    << "\\blong\\b" << "\\bnamespace\\b" << "\\boperator\\b"
                    << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
                    << "\\bshort\\b" << "\\bsignals\\b" << "\\bsigned\\b"
                    << "\\bslots\\b" << "\\bstatic\\b" << "\\bstruct\\b"
                    << "\\btemplate\\b" << "\\btypedef\\b" << "\\btypename\\b"
                    << "\\bunion\\b" << "\\bunsigned\\b" << "\\bvirtual\\b"
                    << "\\bvoid\\b" << "\\bvolatile\\b";

    for (const QString &pattern : keywordPatterns) {
        HighlightingRule rule;
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    // 单行注释
    HighlightingRule singleLineCommentRule;
    singleLineCommentRule.pattern = QRegularExpression("//[^\n]*");
    singleLineCommentRule.format = singleLineCommentFormat;
    highlightingRules.append(singleLineCommentRule);

    // 多行注释
    HighlightingRule multiLineCommentRule;
    multiLineCommentRule.pattern = QRegularExpression("/\\*.*?\\*/");
    multiLineCommentRule.format = multiLineCommentFormat;
    highlightingRules.append(multiLineCommentRule);

    // 字符串
    HighlightingRule quotationRule;
    quotationRule.pattern = QRegularExpression("\".*?\"");
    quotationRule.format = quotationFormat;
    highlightingRules.append(quotationRule);

    // 函数
    HighlightingRule functionRule;
    functionRule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
    functionRule.format = functionFormat;
    highlightingRules.append(functionRule);
}

void SyntaxHighlighter::highlightBlock(const QString &text) {
    for (const HighlightingRule &rule : highlightingRules) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}
