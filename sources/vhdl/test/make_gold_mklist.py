import os

if __name__ == "__main__":
    blacklist = [
         'integer'
    ]
    for root, dirs, files in sorted(os.walk(os.getcwd() + '/' + 'test_case')):
        #print("root=" + str(root))
        subject = os.path.basename(root)
        if subject == 'test_case':
            continue
        subject_base = subject.replace('_failure', '')
        if subject_base in blacklist:
            # don't rewrite, e.g. integer is a simple string_view
            continue
        ast = "ast::" + subject_base
        parser = "parser::" + subject_base
        test_case = "test_case/" + subject
        text = """
{{
    gold_writer<{0}_type, {1}> goldy("{2}");
    goldy.write();
}}""".format(
        parser,
        ast,
        test_case
    )
        print(text)

